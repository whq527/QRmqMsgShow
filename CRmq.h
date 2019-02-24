#pragma once
#include <QObject>
#include <QString>
#include <QStandardItemModel>
#include <QTableView>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition >
#include <QList>
#include <string>
#include <deque>
#include "ClibRmq.h"
#include "cpack.h"

struct st_m_cpack
{
	st_rmq_msg_header header;
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
	void SetData(st_rmq_msg* _msg);
signals:
	//void send_msg_cell(int row, int col, st_m_cpack &);
	void send_msg(st_m_cpack &);
public slots:
	void th_run();

private:
	bool m_stop = false;
	ClibRmq* m_rmq = nullptr;
	bool m_terminated = false;

	QMutex m_mtx;
	QWaitCondition m_wait;
	QList<st_m_cpack> m_recvdata;
};
