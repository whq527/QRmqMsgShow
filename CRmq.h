#pragma once
#include <QObject>
#include <QString>
#include <QStandardItemModel>
#include <QTableView>
#include <QMutex>
#include <QMutexLocker>
#include <QList>
#include <QSemaphore>
#include <string>
#include <deque>
#include "ClibRmq.h"
#include "cpack.h"

struct st_header
{
	//发送参数
	std::string exchange = "";
	std::string routekey = "";
	std::string queue = "";
	time_t timestamp = 0;
	unsigned long src_size = 0;			//原始大小
	//自定义附加属性
	std::string type = "";
	std::string id = "";
};

struct st_m_cpack
{
	st_header header;
	st_cpack pack = { 0 };
};

class CRmq :public QObject
{
	Q_OBJECT
public:
	explicit CRmq();
	virtual ~CRmq();
	bool init(QString _user, QString _psw, QString _ip, int _port, int _channel, QString _queue, QString _consumer, QString _host);
	void th_stop();
	void bindkey(QString _key, QString _exchange);
	void unbindkey(QString _key, QString _exchange);
	//void SetTableView(QTableView * _ptbview);
	void SetData(st_rmq_msg* _msg);
signals:
	void send_msg(st_m_cpack &);
public slots:
	void th_run();

private:
	bool m_stop = false;
	ClibRmq* m_rmq = nullptr;
	bool m_terminated = false;

	QMutex m_mtx;
	//QSemaphore m_sem;
	QList<st_m_cpack> m_recvdata;
};
