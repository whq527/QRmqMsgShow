#include "mainwindow.h"
#include <QApplication>
#include <QMetaType>

#include "CRmq.h"
#include "ClibRmq.h"
#include "cpack.h"

int main(int argc, char *argv[])
{
	qRegisterMetaType<st_rmq_msg>("st_rmq_msg");
	qRegisterMetaType<st_rmq_msg>("st_rmq_msg&");
	qRegisterMetaType<st_rmq_msg_header>("st_rmq_msg_header");
	qRegisterMetaType<st_rmq_msg_header>("st_rmq_msg_header&");

	qRegisterMetaType<st_m_str>("st_m_str");
	qRegisterMetaType<st_m_str>("st_m_str&");

	qRegisterMetaType<st_m_cpack>("st_m_cpack");
	qRegisterMetaType<st_m_cpack>("st_m_cpack&");
	qRegisterMetaType<st_cpack>("st_cpack");
	qRegisterMetaType<st_cpack>("st_cpack&");

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}