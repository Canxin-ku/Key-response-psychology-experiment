#ifndef TEST_H
#define TEST_H

#include <QObject>
#include<QFile>
#include<QTextStream>
#include<QList>


class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = nullptr);

    //词条对应颜色map
    QMap<QString,QList<QString>> mPhCo;

    //词条对应答案map
    QMap<QString,QString> mPhAn;

    //词条容器
    QList<QString> lPhrase;

    //颜色数组
    QList<QString> lColor = {"#FF0000","#008000","#0000FF","#000000","#FFFFFF"};

    //颜色十六进制和文字map
    QMap<QString,QString> mColor;

    //结果
    QList<QString> lResult;

    //读取文件用字符串
    QString str;

    //选择
    QList<QString> lChoose;

    //正确率
    double perSuccess=33.3;

    //写文件函数
    void writeFile();

    //初始化函数
    bool initData(QString fileName);

    //计算正确率
    double calRight();

    //已经写入数据的人数
    int numData=1;

signals:

public slots:
};

#endif // TEST_H
