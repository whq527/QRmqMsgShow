#pragma execution_character_set("utf-8")
#include <QDebug>
#include <QDockWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include "windows.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ClibRmq.h"
#include "FunStr.hpp"
#include "FunCpack.hpp"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	//AllocConsole();
	//freopen("CONOUT$", "w+t", stdout);

	ui->listView_msg->setModel(&m_model_msg);
	//阻止遍历计算item大小, 会有效得降低卡顿
	ui->listView_msg->setUniformItemSizes(true);

	ui->colview_msg->setModel(&m_model_data);
	ui->colview_msg->setResizeGripsVisible(true);

	this->startTimer(500);

	ui->box_key->setCurrentText("");
	ui->edt_bindkey->setText("test #");
	ui->statusBar->addWidget(&m_rmq_status);
	ui->statusBar->addWidget(&m_rmq_bindkey_status);
	m_rmq_status.setText("RMQ 未连接");
}

MainWindow::~MainWindow()
{
	if (m_rmq != nullptr)
		m_rmq->th_stop();
	if (m_threads != nullptr)
	{
		if (m_threads->isRunning())
		{
			m_threads->quit();
			m_threads->wait();
		}
		delete m_threads;
		m_threads = nullptr;
	}

	//FreeConsole();
	delete ui;
}

void MainWindow::on_send_fin()
{
	if (m_rmq != nullptr)
		m_rmq->setready();
}

void MainWindow::on_send_msg_str(st_m_str& _msg)
{
	QStringList strlist;
	strlist << QString::fromStdString(_msg.header.exchange)
		<< QString::fromStdString(_msg.header.routekey)
		<< QDateTime::fromTime_t(_msg.header.timestamp).toString("yyyy-MM-dd hh:mm:ss");
	m_tmp_list << strlist.join("-");

	Fun_Data(&m_model_data, _msg);
}

void MainWindow::on_send_msg_cpack(st_m_cpack& _msg)
{
	QStringList strlist;
	strlist << QString::fromStdString(_msg.header.exchange)
		<< QString::fromStdString(_msg.header.routekey)
		<< QDateTime::fromTime_t(_msg.header.timestamp).toString("yyyy-MM-dd hh:mm:ss");
	m_tmp_list << strlist.join("-");

	Fun_Data(&m_model_data, _msg);
}

void MainWindow::on_btn_start_clicked()
{
	if (ui->btn_start->text() == "启动")
	{
		m_rmq = new CRmq();
		m_threads = new QThread(this);
		connect(m_threads, &QThread::started, m_rmq, &CRmq::th_run);
		connect(m_threads, &QThread::finished, m_rmq, &CRmq::deleteLater);
		connect(m_rmq, &CRmq::send_fin, this, &MainWindow::on_send_fin);
		connect(m_rmq, &CRmq::send_msg_str, this, &MainWindow::on_send_msg_str);
		connect(m_rmq, &CRmq::send_msg_cpack, this, &MainWindow::on_send_msg_cpack);

		if (!m_rmq->init(ui->edt_user->text(), ui->edt_psw->text(), ui->edt_ip->text(), ui->edt_port->text().toInt(), 123, "QRmqMsgShow", "", ui->edt_host->text()))
		{
			QMessageBox::critical(NULL, "错误", "Rabbitmq 连接错误");
		}
		m_rmq->moveToThread(m_threads);
		m_threads->start();
		m_rmq_status.setText(QString("RMQ -> %1").arg(ui->edt_ip->text()));
		ui->btn_start->setText("停止");
	}
	else
	{
		m_rmq->th_stop();
		if (m_threads->isRunning())
		{
			m_threads->quit();
			m_threads->wait();
			delete m_threads;
			m_threads = nullptr;
		}
		m_rmq = nullptr;
		m_rmq_status.setText(QString("停止RMQ -> %1").arg(ui->edt_ip->text()));
		ui->btn_start->setText("启动");
		m_tmp_list.clear();
		m_model_msg.removeRows(0, m_model_msg.rowCount());
		m_model_data.removeRows(0, m_model_data.rowCount());
		m_bindkey.clear();
		ui->box_key->clear();
		m_rmq_bindkey_status.setText(QString("绑定:%1").arg(m_bindkey.join(",")));
	}
}

void MainWindow::on_btn_bind_clicked()
{
	if (m_rmq == nullptr)
		return;
	if (ui->edt_bindkey->text().isEmpty() || ui->edt_bindkey->text() == "exchange key")
		return;

	QString key = ui->edt_bindkey->text().trimmed();
	QString exchange = key.section(' ', 0, 0);
	QString routekey = key.section(' ', -1, -1);
	int idx_bindkey = m_bindkey.indexOf(key);
	//新增
	if (idx_bindkey < 0 && !exchange.isEmpty() && !routekey.isEmpty())
	{
		int idx = ui->box_key->findText(key);
		if (idx < 0)
		{
			m_rmq->bindkey(routekey, exchange);
			ui->box_key->addItem(key);
			m_bindkey << key;
			ui->box_key->setCurrentText("");
		}
	}

	//删除
	if (!ui->box_key->currentText().isEmpty())
	{
		key = ui->box_key->currentText();
		exchange = key.section(' ', 0, 0);
		routekey = key.section(' ', -1, -1);
		m_rmq->unbindkey(routekey, exchange);
		ui->box_key->removeItem(ui->box_key->currentIndex());
		m_bindkey.removeAt(idx_bindkey);
		ui->box_key->setCurrentText("");
	}

	m_rmq_bindkey_status.setText(QString("绑定:%1").arg(m_bindkey.join(",")));
}

void MainWindow::timerEvent(QTimerEvent * event)
{
	Q_UNUSED(event);
	if (m_tmp_list.size() > 0)
	{
		m_model_msg.appendData(m_tmp_list);
		m_tmp_list.clear();
	}
	if (m_rmq != nullptr)
		m_rmq->wakeup();
}