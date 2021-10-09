/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.12.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QPushButton *pushButton_openFile;
    QPushButton *pushButton_sendFile;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_disconnect;
    QPushButton *pushButton_send;
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QProgressBar *progressBar;
    QLineEdit *lineEdit_filename;

    void setupUi(QWidget *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(800, 600);
        pushButton_openFile = new QPushButton(Client);
        pushButton_openFile->setObjectName(QString::fromUtf8("pushButton_openFile"));
        pushButton_openFile->setGeometry(QRect(400, 180, 161, 61));
        pushButton_sendFile = new QPushButton(Client);
        pushButton_sendFile->setObjectName(QString::fromUtf8("pushButton_sendFile"));
        pushButton_sendFile->setGeometry(QRect(600, 180, 161, 61));
        pushButton_connect = new QPushButton(Client);
        pushButton_connect->setObjectName(QString::fromUtf8("pushButton_connect"));
        pushButton_connect->setGeometry(QRect(400, 30, 161, 71));
        pushButton_disconnect = new QPushButton(Client);
        pushButton_disconnect->setObjectName(QString::fromUtf8("pushButton_disconnect"));
        pushButton_disconnect->setGeometry(QRect(610, 30, 151, 71));
        pushButton_send = new QPushButton(Client);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        pushButton_send->setGeometry(QRect(400, 410, 141, 51));
        textEdit = new QTextEdit(Client);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(40, 30, 261, 361));
        lineEdit = new QLineEdit(Client);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 414, 271, 51));
        progressBar = new QProgressBar(Client);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(430, 280, 311, 41));
        progressBar->setValue(24);
        lineEdit_filename = new QLineEdit(Client);
        lineEdit_filename->setObjectName(QString::fromUtf8("lineEdit_filename"));
        lineEdit_filename->setGeometry(QRect(410, 110, 321, 61));

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QWidget *Client)
    {
        Client->setWindowTitle(QApplication::translate("Client", "Client", nullptr));
        pushButton_openFile->setText(QApplication::translate("Client", "open file", nullptr));
        pushButton_sendFile->setText(QApplication::translate("Client", "send file", nullptr));
        pushButton_connect->setText(QApplication::translate("Client", "connect", nullptr));
        pushButton_disconnect->setText(QApplication::translate("Client", "disconnect", nullptr));
        pushButton_send->setText(QApplication::translate("Client", "send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
