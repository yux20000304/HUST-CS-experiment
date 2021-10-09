#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <qdatetime.h>
#include <QLabel>

Widget::Widget(QWidget *parent)
    : QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    lb->resize(1000,200);
    timer->start(1000);
}



Widget::~Widget()
{
    delete ui;
}

void Widget::timerUpdate(void){
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
    lb->setText(str);
}
