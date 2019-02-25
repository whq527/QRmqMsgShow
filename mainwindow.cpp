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

	ui->box_key->setCurrentText("#");
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

//void MainWindow::on_send_msg_cell(int row, int col, st_m_cpack & _msg)
//{
//	Q_UNUSED(row);
//	Q_UNUSED(col);
//	Q_UNUSED(_msg);
//}

void MainWindow::on_send_msg_cpack(st_m_cpack& _msg)
{
	QStringList strlist;
	strlist << QString::fromStdString(_msg.header.exchange)
		<< QString::fromStdString(_msg.header.routekey)
		<< QDateTime::fromTime_t(_msg.header.timestamp).toString("yyyy-MM-dd hh:mm:ss");
	m_tmp_list << strlist.join("-");

	QString exchange = QString::fromStdString(_msg.header.exchange);
	QString routekey = QString::fromStdString(_msg.header.routekey);
	QList<QStandardItem*> plist = m_model_data.findItems(exchange, Qt::MatchExactly, 0);
	if (plist.empty())
	{
		QStandardItem *item_exchange = new QStandardItem(exchange);
		QStandardItem *item_routekey = new QStandardItem(routekey);
		item_exchange->appendRow(item_routekey);
		appendCpack_info(item_routekey, _msg);
		appendCpack_head(item_routekey, _msg);
		appendCpack_pack(item_routekey, _msg);
		m_model_data.appendRow(item_exchange);
	}
	else//找到exchange
	{
		QStandardItem *item_exchange = plist.at(0);
		for (int i = 0; i < item_exchange->rowCount(); i++)//找routekey更新
		{
			QStandardItem *item_routekey = item_exchange->child(i);
			if (routekey == item_routekey->text())
			{
				QStandardItem *item_pack_info = item_routekey->child(0);
				updateCpack_info(item_pack_info, _msg);
				QStandardItem *item_pack_header = item_routekey->child(1);
				updateCpack_head(item_pack_header, _msg);
				QStandardItem *item_pack_pack = item_routekey->child(2);
				updateCpack_pack(item_pack_pack, _msg);
				return;
			}
		}

		// 添加新的routekey
		QStandardItem *item_routekey = new QStandardItem(routekey);
		appendCpack_info(item_routekey, _msg);
		appendCpack_head(item_routekey, _msg);
		appendCpack_pack(item_routekey, _msg);
	}
}

void MainWindow::on_btn_start_clicked()
{
	if (ui->btn_start->text() == "启动")
	{
		m_rmq = new CRmq();
		m_threads = new QThread(this);
		connect(m_threads, &QThread::started, m_rmq, &CRmq::th_run);
		connect(m_threads, &QThread::finished, m_rmq, &CRmq::deleteLater);
		connect(m_rmq, &CRmq::send_msg_cpack, this, &MainWindow::on_send_msg_cpack);
		//connect(this, &MainWindow::wakeup, m_rmq, &CRmq::on_wakeup);
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
		ui->box_key->clear();
	}
}

void MainWindow::on_btn_bind_clicked()
{
	if (ui->box_key->currentText().isEmpty())
		return;
	int idx = ui->box_key->findText(ui->box_key->currentText());
	if (idx == -1)
	{
		m_rmq->bindkey(ui->box_key->currentText(), ui->edt_exchange->text());
		ui->box_key->addItem(ui->box_key->currentText());
		m_bindkey << QString("%1|%2").arg(ui->edt_exchange->text()).arg(ui->box_key->currentText());
		ui->box_key->setCurrentText("");
	}
	else
	{
		m_rmq->unbindkey(ui->box_key->itemText(idx), ui->edt_exchange->text());
		ui->box_key->removeItem(idx);
		m_bindkey.removeAt(idx);
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