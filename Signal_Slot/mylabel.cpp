#include "mylabel.h"
#include<QTime>
#include<QDebug>
#include<time.h>
#include<QTimer>


MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

    fTimer = new QTimer;
    fTimer->setTimerType(Qt::PreciseTimer);
    fTimer->stop();
    fTimer->setInterval(2000);//设置定时周期2s
    connect(fTimer,&QTimer::timeout,this,&MyLabel::timeout);//计时器的超时信号连接超时槽函数


}

void MyLabel::sleep(unsigned int msec)
{
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }

}

void MyLabel::display()
{
    //根据种子生成词条随机数
    qsrand(time(NULL));
    randPhrase = qrand()%t.mPhCo.size();

    //颜色迭代器
    QMap<QString,QList<QString>>::iterator itCo = t.mPhCo.find(t.lPhrase[randPhrase]);
    //答案迭代器
    QMap<QString,QString>::iterator itAn = t.mPhAn.find(t.lPhrase[randPhrase]);

    //生成随机种子
    qsrand(time(NULL));
    //根据种子生成颜色随机数
    randColor = qrand() %itCo.value().size();

    //随机数对应词条显示在Label上
    this->setText(itCo.key());
    //Label的样式
    this->setStyleSheet("font:350px;color:"+itCo.value()[randColor]+";");

    //先记录一部分信息
    temp = t.lPhrase[randPhrase]+"\t"+t.mColor.find(itCo.value()[randColor]).value()
            +"\t"+itAn.value();

    //删除group容器内对应词条的颜色，避免下次随机冲突
    itCo.value().removeAt(randColor);

    tempPhrase = t.lPhrase[randPhrase];

    //判断颜色容器大小
    if(itCo.value().size()==0)
    {
        //移除该词条
        t.mPhCo.remove(t.lPhrase[randPhrase]);
        t.lPhrase.removeAt(randPhrase);
    }



}

void MyLabel::timeout()
{
    //超时写入数据
    if(isTimeout)
    {
        temp = temp+"\t-1\t"+QString::number(fTimeCounter.elapsed(),10)+"ms";
        t.lResult.append(temp);
        t.lChoose.append("-1");//把选择结果存入容器
        qDebug()<<temp;
    }

    //判定是否继续
    if(t.mPhCo.size()==0)
    {
        canChoose = false;
        testOver();
        return;
    }

    isTimeout = true;
    canChoose = false;

    //标签置空
    this->setText(" ");

    //延时2s
    sleep(500);

    //标签设置为注视点
    this->setText("+");
    this->setStyleSheet("font:500px;color:#000000;");

    sleep(500);

    canChoose = true;

    fTimer->start();//定时器开始工作
    fTimeCounter.start();//计时器开始工作

    this->display();


}

void MyLabel::stopTimer(QString phrase)
{
    fTimer->stop();//定时器停止
    int tmMsec = fTimeCounter.elapsed();//获取选择所用时间

    temp = temp+"\t"+phrase+"\t"+QString::number(tmMsec,10)+"ms";//记录时间
    t.lResult.append(temp);//把临时变量存入容器
    t.lChoose.append(phrase);//把选择结果存入容器
    qDebug()<<temp;

    if(t.mPhCo.size()==0)
    {
        canChoose = false;
        testOver();
    }
    else
    {
        isTimeout = false;
        timeout();
    }

}

void MyLabel::testOver()
{
    if(mode==3)
    {
        double temp=t.calRight();
        QString strtemp = QString::number(temp,'f',5);
        if(temp>=80)
        {
            this->setText("测试结束\n正确率为："+strtemp+"\n请按Q键正式实验");
            mode++;//进行正式测试
        }
        else
        {

            this->setText("测试结束\n正确率为："+strtemp+"\n请按Q键重新测试");
            mode=1;
        }
        this->setStyleSheet("font:120px;");
        isTimeout =false;
        fTimer->stop();
    }
    else if(mode==1)
    {
        this->setText("测试结束\n请按Q键返回主界面");
        this->setStyleSheet("font:170px;");
        isTimeout =false;
        fTimer->stop();
        t.writeFile();
        mode=0;
    }
}

void MyLabel::setApp()
{
    switch (mode) {
    case 0:
        this->setText("欢迎\n请按Q键开始实验");
        this->setStyleSheet("font:160px;color:#000000;");
        mode++;
        break;
    case 1:
        this->setText("欢迎参加xxx实验\n"
                      "如果准备好了请按Q键开始练习");
        this->setStyleSheet("font:80px;color:#000000;");
        if(t.initData("./Test.txt"))
        {
            mode++;
        }

        break;
    case 2:
        timeout();
        mode++;
        break;
    case 4:
        if(t.initData("./Actual.txt"))
        {
            mode=1;
            timeout();
        }
    }
}



void MyLabel::testBreak()
{
    this->setText("测试中断");
    this->setStyleSheet("font:250px;");
    isTimeout =false;
    fTimer->stop();
    mode=1;
}
