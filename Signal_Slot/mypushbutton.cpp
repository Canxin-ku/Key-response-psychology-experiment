#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
{

}

void MyPushButton::hideBtn()
{
    this->setVisible(false);
}

void MyPushButton::showBtn()
{
    this->setVisible(true);
}
