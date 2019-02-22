#pragma execution_character_set("utf-8")
#include <QDebug>
#include <QDockWidget>
#include <QTextEdit>
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "windows.h"
#include "ClibRmq.h"

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
	m_rmq->moveToThread(m_threads);
	m_threads->start();

	ui->tableView_msg->setModel(&m_model_msg);
	//ui->tableView_msg->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	//ui->listView_msg->setModel(&m_model_msg);
	//this->startTimer(5000);

	ui->box_key->setCurrentText("two");
	ui->statusBar->addWidget(&m_rmq_status);
	ui->statusBar->addWidget(&m_rmq_bindkey_status);
	m_rmq_status.setText("RMQ 未连接");
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

void MainWindow::on_send_msg(st_m_cpack & _msg)
{
	QStringList strlist;

	if (m_model_msg.rowCount() > 50)
	{
		m_model_msg.removeRow(0);
	}

	strlist << QString::fromStdString(_msg.header.exchange)
		<< QString::fromStdString(_msg.header.routekey)
		<< QDateTime::fromTime_t(_msg.header.timestamp).toString("yyyy-MM-dd hh:mm:ss")
		<< QString::number(_msg.pack.head.recCount);
	m_model_msg.appendRow(new QStandardItem(strlist.join("-")));
	//ui->tableView_msg->resizeColumnsToContents();
}

void MainWindow::on_btn_start_clicked()
{
	if (!m_rmq->init(ui->edt_user->text(), ui->edt_psw->text(), ui->edt_ip->text(), ui->edt_port->text().toInt(), 123, "QRmqMsgShow", "", ui->edt_host->text()))
	{
		QMessageBox::critical(NULL, "错误", "Rabbitmq 连接错误");
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
	m_rmq_bindkey_status.setText(QString("绑定:%1").arg(m_bindkey.join(",")));
}

void MainWindow::timerEvent(QTimerEvent * event)
{
}