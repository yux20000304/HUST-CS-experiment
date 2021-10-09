/********************************************************************************
** Form generated from reading UI file 'server.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_H
#define UI_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Server
{
public:
    QPushButton *pushButton_send;
    QPushButton *pushButton_selectFile;
    QPushButton *pushButton_sendFile;
    QLineEdit *lineEdit;
    QTextBrowser *browser;
    QProgressBar *progressBar_fileProgress;
    QLineEdit *lineEdit_fileName;

    void setupUi(QWidget *Server)
    {
        if (Server->objectName().isEmpty())
            Server->setObjectName(QString::fromUtf8("Server"));
        Server->resize(800, 600);
        pushButton_send = new QPushButton(Server);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        pushButton_send->setGeometry(QRect(390, 380, 121, 51));
        pushButton_selectFile = new QPushButton(Server);
        pushButton_selectFile->setObjectName(QString::fromUtf8("pushButton_selectFile"));
        pushButton_selectFile->setGeometry(QRect(390, 120, 151, 51));
        pushButton_sendFile = new QPushButton(Server);
        pushButton_sendFile->setObjectName(QString::fromUtf8("pushButton_sendFile"));
        pushButton_sendFile->setGeometry(QRect(600, 120, 151, 51));
        lineEdit = new QLineEdit(Server);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(40, 380, 291, 51));
        browser = new QTextBrowser(Server);
        browser->setObjectName(QString::fromUtf8("browser"));
        browser->setGeometry(QRect(40, 20, 291, 311));
        progressBar_fileProgress = new QProgressBar(Server);
        progressBar_fileProgress->setObjectName(QString::fromUtf8("progressBar_fileProgress"));
        progressBar_fileProgress->setGeometry(QRect(390, 60, 361, 41));
        progressBar_fileProgress->setValue(24);
        lineEdit_fileName = new QLineEdit(Server);
        lineEdit_fileName->setObjectName(QString::fromUtf8("lineEdit_fileName"));
        lineEdit_fileName->setGeometry(QRect(380, 200, 361, 61));

        retranslateUi(Server);

        QMetaObject::connectSlotsByName(Server);
    } // setupUi

    void retranslateUi(QWidget *Server)
    {
        Server->setWindowTitle(QApplication::translate("Server", "Server", nullptr));
        pushButton_send->setText(QApplication::translate("Server", "send", nullptr));
        pushButton_selectFile->setText(QApplication::translate("Server", "select file", nullptr));
        pushButton_sendFile->setText(QApplication::translate("Server", "sendfile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Server: public Ui_Server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_H
