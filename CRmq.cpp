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
	st_m_cpack one;
	one.header.exchange = _msg->header.exchange;
	one.header.routekey = _msg->header.routekey;
	one.header.queue = _msg->header.queue;
	one.header.timestamp = _msg->header.timestamp;
	one.header.src_size = _msg->header.src_size;
	one.header.type = _msg->header.type;
	one.header.id = _msg->header.id;
	one.header.struct_name = _msg->header.struct_name;
	if (one.header.src_size == sizeof(ST_CPACK) || one.header.struct_name == "ST_CPACK")
	{
		if (!_msg->header.zlib)
		{
			char m_recvbuf[10240] = { 0 };
			memset(m_recvbuf, 0, sizeof(m_recvbuf));
			unsigned long datalen = sizeof(m_recvbuf);
			uncompress((unsigned char*)m_recvbuf, &datalen, (unsigned char*)_msg->content.bytes, (unsigned long)_msg->content.len);
			if (datalen == sizeof(st_cpack))
			{
				memcpy_s(&one.pack, sizeof(ST_PACK), m_recvbuf, sizeof(ST_PACK));
				QMutexLocker locker(&m_mtx);
				m_recvdata.push_back(one);
				m_wait.notify_all();
			}
		}
		else
		{
			memcpy_s(&one.pack, sizeof(ST_PACK), _msg->content.bytes, sizeof(ST_PACK));
			QMutexLocker locker(&m_mtx);
			m_recvdata.push_back(one);
			m_wait.notify_all();
		}
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
		st_m_cpack one;
		{
			QMutexLocker locker(&m_mtx);
			if (m_recvdata.size() > 0)
			{
				emit send_msg(m_recvdata.front());
				m_recvdata.pop_front();
				found = true;
			}
		}

		if (!found)
		{
			QMutexLocker locker(&m_mtx);
			m_wait.wait(&m_mtx);
		}
	}
}