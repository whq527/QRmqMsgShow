#pragma execution_character_set("utf-8")
#include <QDebug>
#include <QTime>
#include "CRmq.h"
#include "zlib.h"

CRmq* g_pth;

void __stdcall OnRMQData(st_rmq_msg* msg)
{
	g_pth->SetData(msg);
}

CRmq::CRmq()
{
	g_pth = this;
}

CRmq::~CRmq()
{
	if (m_rmq == nullptr)
		return;
	m_rmq->Terminate();
	m_rmq->Join();
	delete m_rmq;
	m_rmq = nullptr;
}

bool CRmq::init(QString _user, QString _psw, QString _ip, int _port, int _channel, QString _queue, QString _consumer, QString _host)
{
	if (m_rmq == nullptr)
	{
		m_rmq = new ClibRmq(_channel);
		QByteArray user = _user.toLocal8Bit();
		QByteArray psw = _psw.toLocal8Bit();
		QByteArray ip = _ip.toLocal8Bit();
		QByteArray queue = _queue.toLocal8Bit();
		QByteArray consumer = _consumer.toLocal8Bit();
		QByteArray host = _host.toLocal8Bit();
		if (!m_rmq->Init(user.data(), psw.data(), ip.data(),
			_port, "", "", 1, EM_WORKTYPE::CUSTOMER, true, OnRMQData, queue.data(), consumer.data(), 1, host.data()))
		{
			delete m_rmq;
			m_rmq = nullptr;
			return false;
		}
		m_rmq->Start();
	}
	return true;
}

void CRmq::bindkey(QString _key, QString _exchange)
{
	if (m_rmq == nullptr)
		return;
	QByteArray key = _key.toLocal8Bit();
	QByteArray exchange = _exchange.toLocal8Bit();
	m_rmq->Get_Bind(key.data(), exchange.data());
}

void CRmq::unbindkey(QString _key, QString _exchange)
{
	if (m_rmq == nullptr)
		return;
	QByteArray key = _key.toLocal8Bit();
	QByteArray exchange = _exchange.toLocal8Bit();
	m_rmq->Get_UnBind(key.data(), exchange.data());
}

void CRmq::SetData(st_rmq_msg * _msg)
{
	st_rmq_msg_header header;
	header.exchange = _msg->header.exchange;
	header.routekey = _msg->header.routekey;
	header.queue = _msg->header.queue;
	header.timestamp = _msg->header.timestamp;
	header.zlib = _msg->header.zlib;
	header.src_size = _msg->header.src_size;
	header.type = _msg->header.type;
	header.id = _msg->header.id;
	header.struct_name = _msg->header.struct_name;

	if (header.src_size == sizeof(ST_CPACK) || header.struct_name == "ST_CPACK")
	{
		st_m_cpack one;
		one.header = header;
		one.update = true;

		memcpy_s(&one.pack, sizeof(ST_PACK), _msg->content.bytes, sizeof(ST_PACK));
		QMutexLocker locker(&m_mtx);
		m_recvdata_cpack.push_back(one);
		m_wait.notify_all();
	}
	else if (header.struct_name == "string" || header.struct_name.empty())
	{
		st_m_str one;
		one.header = header;
		one.update = true;

		one.pack = { (char*)_msg->content.bytes,_msg->content.len };
		QMutexLocker locker(&m_mtx);
		m_recvdata_str.push_back(one);
		m_wait.notify_all();
	}
}

void CRmq::th_stop()
{
	m_stop = true;
	QMutexLocker locker(&m_mtx);
	m_wait.notify_all();
	if (m_rmq == nullptr)
		return;
	m_rmq->Terminate();
}

void CRmq::th_run()
{
	while (m_stop != true)
	{
		bool found = false;
		st_m_str one_str;
		{
			QMutexLocker locker(&m_mtx);
			if (m_recvdata_str.size() > 0)
			{
				one_str.header = m_recvdata_str.front().header;
				one_str.update = m_recvdata_str.front().update;
				one_str.pack = m_recvdata_str.front().pack;
				m_recvdata_str.pop_front();
				found = true;
			}
		}
		if (found)
		{
			QString key = QString("%1_%2").arg(QString::fromStdString(one_str.header.exchange)).arg(QString::fromStdString(one_str.header.routekey));
			m_recvdata_str_map[key] = one_str;
		}

		found = false;
		st_m_cpack one_cpack;
		{
			QMutexLocker locker(&m_mtx);
			if (m_recvdata_cpack.size() > 0)
			{
				one_cpack.header = m_recvdata_cpack.front().header;
				one_cpack.update = m_recvdata_cpack.front().update;
				memcpy_s(&one_cpack.pack, sizeof(ST_CPACK), &m_recvdata_cpack.front().pack, sizeof(ST_CPACK));
				m_recvdata_cpack.pop_front();
				found = true;
			}
		}
		if (found)
		{
			QString key = QString("%1_%2").arg(QString::fromStdString(one_cpack.header.exchange)).arg(QString::fromStdString(one_cpack.header.routekey));
			m_recvdata_cpack_map[key] = one_cpack;
		}

		if (m_ready)
		{
			for (auto var = m_recvdata_str_map.begin(); var != m_recvdata_str_map.end(); var++)
			{
				if (var->update)
				{
					emit send_msg_str(*var);
					var->update = false;
				}
			}
			for (auto var = m_recvdata_cpack_map.begin(); var != m_recvdata_cpack_map.end(); var++)
			{
				if (var->update)
				{
					emit send_msg_cpack(*var);
					var->update = false;
				}
			}
			m_ready = false;
			emit send_fin();
		}

		if (!found)
		{
			QMutexLocker locker(&m_mtx);
			m_wait.wait(&m_mtx);
		}
	}
}

void CRmq::wakeup()
{
	QMutexLocker locker(&m_mtx);
	m_wait.notify_all();
}