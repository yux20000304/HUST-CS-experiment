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
