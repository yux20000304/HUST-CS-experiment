/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qchartview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_CurrentTime;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_runningtime;
    QVBoxLayout *verticalLayout;
    QLabel *label_6;
    QLabel *label_boot_time;
    QSpacerItem *verticalSpacer;
    QLabel *label_5;
    QLabel *label_hostname;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_7;
    QLabel *label_SystemVersion;
    QLabel *label_4;
    QLabel *cpu_rate;
    QtCharts::QChartView *cpu_chart;
    QLabel *label_3;
    QProgressBar *progressBar_RAM;
    QListWidget *listWidget_process;
    QLabel *label_CPUType;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1941, 1847);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        verticalLayout_3->addWidget(label);

        label_CurrentTime = new QLabel(centralwidget);
        label_CurrentTime->setObjectName(QString::fromUtf8("label_CurrentTime"));

        verticalLayout_3->addWidget(label_CurrentTime);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        label_runningtime = new QLabel(centralwidget);
        label_runningtime->setObjectName(QString::fromUtf8("label_runningtime"));

        verticalLayout_2->addWidget(label_runningtime);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        verticalLayout->addWidget(label_6);

        label_boot_time = new QLabel(centralwidget);
        label_boot_time->setObjectName(QString::fromUtf8("label_boot_time"));

        verticalLayout->addWidget(label_boot_time);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);

        verticalLayout->addWidget(label_5);

        label_hostname = new QLabel(centralwidget);
        label_hostname->setObjectName(QString::fromUtf8("label_hostname"));

        verticalLayout->addWidget(label_hostname);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);

        verticalLayout->addWidget(label_7);

        label_SystemVersion = new QLabel(centralwidget);
        label_SystemVersion->setObjectName(QString::fromUtf8("label_SystemVersion"));

        verticalLayout->addWidget(label_SystemVersion);


        verticalLayout_4->addLayout(verticalLayout);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setFont(font);

        verticalLayout_4->addWidget(label_4);

        cpu_rate = new QLabel(centralwidget);
        cpu_rate->setObjectName(QString::fromUtf8("cpu_rate"));

        verticalLayout_4->addWidget(cpu_rate);

        cpu_chart = new QtCharts::QChartView(centralwidget);
        cpu_chart->setObjectName(QString::fromUtf8("cpu_chart"));

        verticalLayout_4->addWidget(cpu_chart);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font);

        verticalLayout_4->addWidget(label_3);

        progressBar_RAM = new QProgressBar(centralwidget);
        progressBar_RAM->setObjectName(QString::fromUtf8("progressBar_RAM"));
        progressBar_RAM->setValue(24);

        verticalLayout_4->addWidget(progressBar_RAM);

        listWidget_process = new QListWidget(centralwidget);
        listWidget_process->setObjectName(QString::fromUtf8("listWidget_process"));

        verticalLayout_4->addWidget(listWidget_process);

        label_CPUType = new QLabel(centralwidget);
        label_CPUType->setObjectName(QString::fromUtf8("label_CPUType"));

        verticalLayout_4->addWidget(label_CPUType);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout_4->addWidget(lineEdit);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_4->addWidget(pushButton_2);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_4->addWidget(pushButton);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1941, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "current time", nullptr));
        label_CurrentTime->setText(QApplication::translate("MainWindow", "current time", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "run time", nullptr));
        label_runningtime->setText(QApplication::translate("MainWindow", "running time", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "boot time", nullptr));
        label_boot_time->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "host name", nullptr));
        label_hostname->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "kernel version", nullptr));
        label_SystemVersion->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "CPU RATE", nullptr));
        cpu_rate->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Memory ratio", nullptr));
        label_CPUType->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "kill", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "shutdown", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
