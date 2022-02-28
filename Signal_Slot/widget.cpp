#include "widget.h"
#include "ui_widget.h"
#include<QTime>
#include<QDebug>
#include"test.h"
#include<QApplication>
#include<QDesktopWidget>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect clientRect = desktopWidget->availableGeometry();

    int ScreenWidth = clientRect.width();
    int ScreenHeight = clientRect.height();
    qDebug()<<ScreenWidth<<" "<<ScreenHeight;

    int labelWidth = ScreenWidth*3/4;
    int labelHeight = ScreenHeight*2/3;
    qDebug()<<labelWidth<<" "<<labelHeight;

    //窗口设置
    setAutoFillBackground(true);
    setPalette(QPalette(QColor(169,169,169)));
    setGeometry(0,0,ScreenWidth,ScreenHeight);

    //标签设置
    myLab->setGeometry((ScreenWidth-labelWidth)/2,(ScreenHeight-labelHeight)/3,labelWidth,labelHeight);
    myLab->setAlignment(Qt::AlignCenter);
    myLab->setText("欢迎\n请按Q键开始实验");
    myLab->setStyleSheet("font:160px;color:#000000;");
    myLab->setParent(this);

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_F:
        if(myLab->canChoose)
        {
            myLab->stopTimer("0");
        }
        break;
    case Qt::Key_J:
        if(myLab->canChoose)
        {
            myLab->stopTimer("1");
        }
        break;
    case Qt::Key_P:
        myLab->testBreak();
        break;
    case Qt::Key_Escape:
        this->close();
        break;
    case Qt::Key_Q:
        myLab->setApp();
        break;
    }

}

Widget::~Widget()
{
    delete ui;
}
