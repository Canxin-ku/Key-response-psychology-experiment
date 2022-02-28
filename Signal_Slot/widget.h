#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"mylabel.h"
#include<QKeyEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    MyLabel *myLab = new MyLabel;//标签对象


    void keyPressEvent(QKeyEvent *event);


    ~Widget();

private:
    Ui::Widget *ui;

};

#endif // WIDGET_H
