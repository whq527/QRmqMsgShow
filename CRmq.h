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
	bool update = false;
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
	void wakeup();
	//全部推送设置ready=false, 等fin 的emit的信号到主线程, 说明全部处理完毕, 再用主线程设置标识, 等计时器的timeout, 开始下一次更新
	void setready() { m_ready = true; }
signals:
	void send_fin();
	void send_msg_cpack(st_m_cpack&);
public slots:
	void th_run();

private:
	bool m_stop = false;
	ClibRmq* m_rmq = nullptr;
	bool m_terminated = false;
	bool m_ready = true;

	QMutex m_mtx;
	QWaitCondition m_wait;
	QList<st_m_cpack> m_recvdata_cpack;
	QMap<QString, st_m_cpack> m_recvdata_cpack_map;
};
