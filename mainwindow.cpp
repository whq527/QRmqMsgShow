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
#include "FunCpack.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	//AllocConsole();
	//freopen("CONOUT$", "w+t", stdout);
	m_threads = new QThread(this);
	m_rmq = new CRmq();
	connect(m_threads, &QThread::started, m_rmq, &CRmq::th_run);
	connect(m_threads, &QThread::finished, m_rmq, &CRmq::deleteLater);
	connect(m_rmq, &CRmq::send_msg, this, &MainWindow::on_send_msg);
	//connect(m_rmq, &CRmq::send_msg_cell, this, &MainWindow::on_send_msg_cell);
	m_rmq->moveToThread(m_threads);
	m_threads->start();

	ui->listView_msg->setModel(&m_model_msg);
	//��ֹ��������item��С, ����Ч�ý��Ϳ���
	ui->listView_msg->setUniformItemSizes(true);

	ui->colview_msg->setModel(&m_model_data);
	ui->colview_msg->setResizeGripsVisible(true);

	this->startTimer(50);

	ui->box_key->setCurrentText("#");
	ui->statusBar->addWidget(&m_rmq_status);
	ui->statusBar->addWidget(&m_rmq_bindkey_status);
	m_rmq_status.setText("RMQ δ����");
}

MainWindow::~MainWindow()
{
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

void MainWindow::on_send_msg(st_m_cpack & _msg)
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
		appendCpack_head(item_routekey, _msg);
		appendCpack_pack(item_routekey, _msg);
		m_model_data.appendRow(item_exchange);
	}
	else//�ҵ�exchange
	{
		bool found = false;
		QStandardItem *item_exchange = plist.at(0);
		for (int i = 0; i < item_exchange->rowCount(); i++)//��routekey
		{
			QStandardItem *item_routekey = item_exchange->child(i);
			if (routekey == item_routekey->text())
			{
				QStandardItem *item_pack_header = item_routekey->child(0);
				updateCpack_head(item_pack_header, _msg);
				QStandardItem *item_pack_pack = item_routekey->child(1);
				updateCpack_pack(item_pack_pack, _msg);
				found = true;
			}
		}
		if (!found)//����µ�routekey
		{
			QStandardItem *item_routekey = new QStandardItem(routekey);
			appendCpack_head(item_routekey, _msg);
			appendCpack_pack(item_routekey, _msg);
			item_exchange->appendRow(item_routekey);
		}
	}
}

void MainWindow::on_btn_start_clicked()
{
	if (!m_rmq->init(ui->edt_user->text(), ui->edt_psw->text(), ui->edt_ip->text(), ui->edt_port->text().toInt(), 123, "QRmqMsgShow", "", ui->edt_host->text()))
	{
		QMessageBox::critical(NULL, "����", "Rabbitmq ���Ӵ���");
	}
	m_rmq_status.setText(QString("RMQ -> %1").arg(ui->edt_ip->text()));
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
	}
	else
	{
		m_rmq->unbindkey(ui->box_key->itemText(idx), ui->edt_exchange->text());
		ui->box_key->removeItem(idx);
		m_bindkey.removeAt(idx);
	}
	m_rmq_bindkey_status.setText(QString("��:%1").arg(m_bindkey.join(",")));
}

void MainWindow::timerEvent(QTimerEvent * event)
{
	Q_UNUSED(event);
	if (m_tmp_list.size() > 0)
	{
		m_model_msg.appendData(m_tmp_list);
		m_tmp_list.clear();
	}
}