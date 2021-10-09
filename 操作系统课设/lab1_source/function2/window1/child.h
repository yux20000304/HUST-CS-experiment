#ifndef CHILD_H
#define CHILD_H

#include <QWidget>

class child : public QWidget
{
    Q_OBJECT
public:
    explicit child(QWidget *parent = nullptr);

signals:

};

#endif // CHILD_H
