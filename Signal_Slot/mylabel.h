#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include"test.h"
#include<QTime>
#include<QCoreApplication>
#include<QTimer>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

    Test t;//实验对象

    int randPhrase,randColor;//随机数

    bool canChoose;

    bool isTimeout = false;

    QString temp;//临时保存数据

    void sleep(unsigned int msec);//延时函数

    void display();//显示函数

    void testOver();//实验结束

    void stopTimer(QString phrase);//停止计时

    void testBreak();//测试中断

    int mode=1;//软件进程模式

    QString tempPhrase;//临时实验的变量

    QString sGuide;//指导语

    QTimer *fTimer;//定时器
    QTime fTimeCounter;//计时器

    void setApp();//设置标签样式

signals:


public slots:
    void timeout();//timer超时






};

#endif // MYLABEL_H
