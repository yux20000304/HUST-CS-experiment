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
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *cpu_rate;
    QTextEdit *label_CurrentTime;
    QProgressBar *progressBar_RAM;
    QTabWidget *tabWidget_INFO;
    QWidget *list;
    QWidget *tab_2;
    QLabel *label_runningtime;
    QLabel *label_hostname;
    QLabel *label_boottime;
    QLabel *label_CPUType;
    QLabel *label_SystemVersion;
    QListWidget *listWidget_process;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1976, 1179);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        cpu_rate = new QTextEdit(centralwidget);
        cpu_rate->setObjectName(QString::fromUtf8("cpu_rate"));
        cpu_rate->setGeometry(QRect(60, 20, 491, 121));
        label_CurrentTime = new QTextEdit(centralwidget);
        label_CurrentTime->setObjectName(QString::fromUtf8("label_CurrentTime"));
        label_CurrentTime->setGeometry(QRect(60, 170, 501, 151));
        progressBar_RAM = new QProgressBar(centralwidget);
        progressBar_RAM->setObjectName(QString::fromUtf8("progressBar_RAM"));
        progressBar_RAM->setGeometry(QRect(1370, 660, 361, 121));
        progressBar_RAM->setValue(24);
        tabWidget_INFO = new QTabWidget(centralwidget);
        tabWidget_INFO->setObjectName(QString::fromUtf8("tabWidget_INFO"));
        tabWidget_INFO->setGeometry(QRect(30, 380, 521, 501));
        list = new QWidget();
        list->setObjectName(QString::fromUtf8("list"));
        tabWidget_INFO->addTab(list, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget_INFO->addTab(tab_2, QString());
        label_runningtime = new QLabel(centralwidget);
        label_runningtime->setObjectName(QString::fromUtf8("label_runningtime"));
        label_runningtime->setGeometry(QRect(740, 130, 311, 101));
        label_hostname = new QLabel(centralwidget);
        label_hostname->setObjectName(QString::fromUtf8("label_hostname"));
        label_hostname->setGeometry(QRect(740, 260, 291, 101));
        label_boottime = new QLabel(centralwidget);
        label_boottime->setObjectName(QString::fromUtf8("label_boottime"));
        label_boottime->setGeometry(QRect(738, 393, 291, 101));
        label_CPUType = new QLabel(centralwidget);
        label_CPUType->setObjectName(QString::fromUtf8("label_CPUType"));
        label_CPUType->setGeometry(QRect(740, 540, 301, 71));
        label_SystemVersion = new QLabel(centralwidget);
        label_SystemVersion->setObjectName(QString::fromUtf8("label_SystemVersion"));
        label_SystemVersion->setGeometry(QRect(730, 670, 331, 101));
        listWidget_process = new QListWidget(centralwidget);
        listWidget_process->setObjectName(QString::fromUtf8("listWidget_process"));
        listWidget_process->setGeometry(QRect(1380, 120, 491, 311));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1976, 48));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget_INFO->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        tabWidget_INFO->setTabText(tabWidget_INFO->indexOf(list), QApplication::translate("MainWindow", "Tab 1", nullptr));
        tabWidget_INFO->setTabText(tabWidget_INFO->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", nullptr));
        label_runningtime->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_hostname->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_boottime->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_CPUType->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        label_SystemVersion->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
