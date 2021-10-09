#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>

namespace Ui{
class Widget;
}


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    QLabel *lb=new QLabel(this);
    ~Widget();
private:
    Ui::Widget *ui;

public slots:
    void timerUpdate(void);
};
#endif // WIDGET_H



#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}



#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <qdatetime.h>
#include <QLabel>
#include "mypushbutton.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
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

