#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QLabel>
#include "CWListModel.h"
#include "libMsgTcpIter.h"
#include "CRmq.h"
#include "ClibRmq.h"
#include "cpack.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

signals:
	void th_stop();
	void wakeup();
private slots:
	void on_send_msg_cpack(st_m_cpack& _msg);
	void on_btn_start_clicked();
	void on_btn_bind_clicked();
protected:
	//����һ���麯������QEvent�̳ж���.
	virtual void timerEvent(QTimerEvent*event);
private:
	Ui::MainWindow *ui;
	QLabel m_rmq_status;
	QLabel m_rmq_bindkey_status;
	QStringList m_bindkey;

	QThread* m_threads;
	ClibMsg *msg = nullptr;
	CRmq *m_rmq = nullptr;

	QStringList m_tmp_list;
	CWListModel m_model_msg;
	QStandardItemModel m_model_data;
};

#endif // MAINWINDOW_H
