#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QStandardItemModel>
#include <QLabel>
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

private slots:
	void on_send_msg(st_m_cpack & _msg);
	void on_btn_start_clicked();
	void on_btn_bind_clicked();
protected:
	//这是一个虚函数，从QEvent继承而来.
	virtual void timerEvent(QTimerEvent*event);
private:
	Ui::MainWindow *ui;
	QLabel m_rmq_status;
	QLabel m_rmq_bindkey_status;
	QStringList m_bindkey;

	QThread* m_threads;
	ClibMsg *msg = nullptr;
	CRmq *m_rmq = nullptr;

	QStandardItemModel m_model_msg;
	int count = 0;
};

#endif // MAINWINDOW_H
