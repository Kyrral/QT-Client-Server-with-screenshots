/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QListWidget *list_files;
    QLabel *label_clients;
    QListWidget *list_clients;
    QLabel *label_files;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QPushButton *btn_request;
    QLabel *label_chosenFile;
    QLabel *label_file_input;
    QSpacerItem *horizontalSpacer;
    QLabel *label_client_input;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_chosenClient;
    QSpacerItem *verticalSpacer;
    QLabel *label_pic;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(906, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(450, 9, 451, 541));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(10);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        list_files = new QListWidget(gridLayoutWidget);
        list_files->setObjectName("list_files");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(list_files->sizePolicy().hasHeightForWidth());
        list_files->setSizePolicy(sizePolicy);

        gridLayout->addWidget(list_files, 1, 0, 1, 1);

        label_clients = new QLabel(gridLayoutWidget);
        label_clients->setObjectName("label_clients");

        gridLayout->addWidget(label_clients, 0, 1, 1, 1);

        list_clients = new QListWidget(gridLayoutWidget);
        list_clients->setObjectName("list_clients");
        sizePolicy.setHeightForWidth(list_clients->sizePolicy().hasHeightForWidth());
        list_clients->setSizePolicy(sizePolicy);

        gridLayout->addWidget(list_clients, 1, 1, 1, 1);

        label_files = new QLabel(gridLayoutWidget);
        label_files->setObjectName("label_files");

        gridLayout->addWidget(label_files, 0, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralwidget);
        gridLayoutWidget_2->setObjectName("gridLayoutWidget_2");
        gridLayoutWidget_2->setGeometry(QRect(10, 9, 361, 101));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        btn_request = new QPushButton(gridLayoutWidget_2);
        btn_request->setObjectName("btn_request");
        btn_request->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btn_request->sizePolicy().hasHeightForWidth());
        btn_request->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(btn_request, 3, 2, 1, 1);

        label_chosenFile = new QLabel(gridLayoutWidget_2);
        label_chosenFile->setObjectName("label_chosenFile");

        gridLayout_2->addWidget(label_chosenFile, 1, 1, 1, 1);

        label_file_input = new QLabel(gridLayoutWidget_2);
        label_file_input->setObjectName("label_file_input");

        gridLayout_2->addWidget(label_file_input, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 3, 1, 1, 1);

        label_client_input = new QLabel(gridLayoutWidget_2);
        label_client_input->setObjectName("label_client_input");

        gridLayout_2->addWidget(label_client_input, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        label_chosenClient = new QLabel(gridLayoutWidget_2);
        label_chosenClient->setObjectName("label_chosenClient");

        gridLayout_2->addWidget(label_chosenClient, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 2, 1, 1);

        label_pic = new QLabel(centralwidget);
        label_pic->setObjectName("label_pic");
        label_pic->setGeometry(QRect(18, 135, 351, 261));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 906, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Server", nullptr));
        label_clients->setText(QCoreApplication::translate("MainWindow", "Clients:", nullptr));
        label_files->setText(QCoreApplication::translate("MainWindow", "Files:", nullptr));
        btn_request->setText(QCoreApplication::translate("MainWindow", "Request", nullptr));
        label_chosenFile->setText(QString());
        label_file_input->setText(QCoreApplication::translate("MainWindow", "File: ", nullptr));
        label_client_input->setText(QCoreApplication::translate("MainWindow", "Client: ", nullptr));
        label_chosenClient->setText(QString());
        label_pic->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
