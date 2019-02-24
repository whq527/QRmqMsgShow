/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QColumnView>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QListView *listView_msg;
    QColumnView *colview_msg;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget_1;
    QWidget *dockWidgetContents_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *edt_ip;
    QLabel *label_2;
    QLineEdit *edt_port;
    QPushButton *btn_start;
    QLabel *label_4;
    QLineEdit *edt_exchange;
    QComboBox *box_key;
    QPushButton *btn_bind;
    QLabel *label_5;
    QLineEdit *edt_user;
    QLabel *label_6;
    QLineEdit *edt_psw;
    QLabel *label_3;
    QLineEdit *edt_host;
    QSpacerItem *horizontalSpacer;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_6;
    QHBoxLayout *horizontalLayout;
    QLabel *label_7;
    QLineEdit *edt_filter;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1054, 612);
        MainWindow->setDocumentMode(false);
        MainWindow->setDockNestingEnabled(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        listView_msg = new QListView(centralWidget);
        listView_msg->setObjectName(QString::fromUtf8("listView_msg"));
        listView_msg->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_2->addWidget(listView_msg);

        colview_msg = new QColumnView(centralWidget);
        colview_msg->setObjectName(QString::fromUtf8("colview_msg"));

        horizontalLayout_2->addWidget(colview_msg);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1054, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidget_1 = new QDockWidget(MainWindow);
        dockWidget_1->setObjectName(QString::fromUtf8("dockWidget_1"));
        dockWidget_1->setMinimumSize(QSize(741, 100));
        dockWidget_1->setMaximumSize(QSize(524287, 100));
        dockWidget_1->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        verticalLayout_3 = new QVBoxLayout(dockWidgetContents_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_2 = new QGroupBox(dockWidgetContents_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        edt_ip = new QLineEdit(groupBox_2);
        edt_ip->setObjectName(QString::fromUtf8("edt_ip"));
        edt_ip->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_4->addWidget(edt_ip);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        edt_port = new QLineEdit(groupBox_2);
        edt_port->setObjectName(QString::fromUtf8("edt_port"));
        edt_port->setMaximumSize(QSize(32, 16777215));

        horizontalLayout_4->addWidget(edt_port);

        btn_start = new QPushButton(groupBox_2);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));

        horizontalLayout_4->addWidget(btn_start);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_4->addWidget(label_4);

        edt_exchange = new QLineEdit(groupBox_2);
        edt_exchange->setObjectName(QString::fromUtf8("edt_exchange"));
        edt_exchange->setMaximumSize(QSize(128, 16777215));

        horizontalLayout_4->addWidget(edt_exchange);

        box_key = new QComboBox(groupBox_2);
        box_key->setObjectName(QString::fromUtf8("box_key"));
        box_key->setEditable(true);
        box_key->setDuplicatesEnabled(false);

        horizontalLayout_4->addWidget(box_key);

        btn_bind = new QPushButton(groupBox_2);
        btn_bind->setObjectName(QString::fromUtf8("btn_bind"));

        horizontalLayout_4->addWidget(btn_bind);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_4->addWidget(label_5);

        edt_user = new QLineEdit(groupBox_2);
        edt_user->setObjectName(QString::fromUtf8("edt_user"));
        edt_user->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_4->addWidget(edt_user);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        edt_psw = new QLineEdit(groupBox_2);
        edt_psw->setObjectName(QString::fromUtf8("edt_psw"));
        edt_psw->setMaximumSize(QSize(64, 16777215));

        horizontalLayout_4->addWidget(edt_psw);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        edt_host = new QLineEdit(groupBox_2);
        edt_host->setObjectName(QString::fromUtf8("edt_host"));
        edt_host->setMaximumSize(QSize(32, 16777215));

        horizontalLayout_4->addWidget(edt_host);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        verticalLayout_3->addWidget(groupBox_2);

        dockWidget_1->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(4), dockWidget_1);
        dockWidget_2 = new QDockWidget(MainWindow);
        dockWidget_2->setObjectName(QString::fromUtf8("dockWidget_2"));
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QString::fromUtf8("dockWidgetContents_6"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents_6);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_7 = new QLabel(dockWidgetContents_6);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout->addWidget(label_7);

        edt_filter = new QLineEdit(dockWidgetContents_6);
        edt_filter->setObjectName(QString::fromUtf8("edt_filter"));

        horizontalLayout->addWidget(edt_filter);

        dockWidget_2->setWidget(dockWidgetContents_6);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Rabbitmq", nullptr));
        label->setText(QApplication::translate("MainWindow", "IP", nullptr));
        edt_ip->setText(QApplication::translate("MainWindow", "192.168.3.200", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "PORT", nullptr));
        edt_port->setText(QApplication::translate("MainWindow", "5672", nullptr));
        btn_start->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Exchange+key", nullptr));
        edt_exchange->setText(QApplication::translate("MainWindow", "test", nullptr));
        btn_bind->setText(QApplication::translate("MainWindow", "\347\273\221\345\256\232/\350\247\243\347\273\221", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "User", nullptr));
        edt_user->setText(QApplication::translate("MainWindow", "client", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "Psw", nullptr));
        edt_psw->setText(QApplication::translate("MainWindow", "client", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "host", nullptr));
        edt_host->setText(QApplication::translate("MainWindow", "/", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\350\277\207\346\273\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
