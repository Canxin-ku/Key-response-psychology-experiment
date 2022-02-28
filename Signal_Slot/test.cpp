#include "test.h"
#include<QDebug>
#include<QTextCodec>
#include<QMessageBox>

Test::Test(QObject *parent) : QObject(parent)
{
    mColor.insert(lColor[0],"红色");
    mColor.insert(lColor[1],"绿色");
    mColor.insert(lColor[2],"蓝色");
    mColor.insert(lColor[3],"黑色");
    mColor.insert(lColor[4],"白色");
}

//读文件
bool Test::initData(QString fileName)
{
    mPhAn.clear();
    mPhCo.clear();
    lPhrase.clear();
    lResult.clear();
    lChoose.clear();
    QFile rFile(fileName);
    if(!rFile.exists())
    {
        rFile.open(QIODevice::WriteOnly|QIODevice::Text);
        QMessageBox::about(NULL,"提示","词库文件为空");
        return false;
    }
    rFile.open(QIODevice::ReadOnly|QIODevice::Text);
    if (rFile.size()==0)
    {
        QMessageBox::about(NULL,"提示","词库文件为空");
        return false;
    }
    QTextStream aStream(&rFile);
    aStream.setAutoDetectUnicode(true);
    while(!aStream.atEnd())
    {
        //读取一行
        str = aStream.readLine();
        //根据空格分割字符串
        QStringList ql = str.split(' ');
        //写入容器
        mPhAn.insert(ql[0],ql[1]);
        mPhCo.insert(ql[0],lColor);
        lPhrase.append(ql[0]);

    }
    rFile.close();
    return true;
}

void Test::writeFile()
{
    calRight();
    //写入
    QFile wFile("./Result.txt");
//    if(!wFile.exists())
//    {
//        wFile.open(QIODevice::ReadWrite|QIODevice::Text);


//    }
//    else
    wFile.open(QIODevice::ReadWrite|QIODevice::Append|QIODevice::Text);
    //读取文件第一行，获取人数
    QTextStream aStream(&wFile);
    aStream.setAutoDetectUnicode(true);
    aStream.seek(0);//定位到第一行
    QString strData = aStream.readLine();//获取第一行数据
    //qDebug()<<strData;
    if(strData=="")//若第一行没有数据代表文件刚写入，实验人数为0
    {
        numData = 1;
    }
    else
    {
        QStringList slNum = strData.split("：");//分割符
        QString sNumTest = slNum[1];//获取人数
        int iNumTest = sNumTest.toInt();//转为int类型
        //qDebug()<<iNumTest;
        numData = iNumTest + 1;//更新实验人数
    }


    qint64 fileSize = wFile.size();//获取文件字节数
    //qDebug()<<fileSize;

    QTextStream wStream(&wFile);
    wStream.setCodec("utf-8");
    wStream.seek(fileSize);//定位到文件最后的位置
    QString sNO = ("被试序号：");
    QString sPerRight("正确率：");
    int iNo=1;
    wStream<<"               "<<endl<<endl<<sNO<<numData<<"\t"<<sPerRight<<perSuccess<<'%'<<endl;
    //qDebug()<<lResult.size();
    for(QList<QString>::iterator it=lResult.begin();it!=lResult.end();it++)
    {
        wStream<<iNo<<"\t";
        wStream<<*it<<endl;
        iNo++;
    }
    //定位到第一行，重写数据
    wStream.seek(0);
    QString str2("写入人数：");
    wStream<<str2<<numData;
    wFile.close();
}

double Test::calRight()
{
    //计算正确率
    double iRight=0.0;
    double iSize=lChoose.size();
    for(int i=0;i<lResult.size();i++)
    {
        //对比答案
        QStringList ql = lResult[i].split("\t");//依据\t分割字符串并形成列表
        QString temp = ql[2];//获取列表中的答案的值
        int n =QString::compare(temp,lChoose[i]);
        if(n==0)//如果答案和选择的值相同
        {
            iRight++;
        }
    }
//    qDebug()<<iRight;
//    qDebug()<<iSize;
    perSuccess = (iRight/iSize)*100;
    return perSuccess;
}
