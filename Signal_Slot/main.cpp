#include "widget.h"
#include <QApplication>
#include<QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    QApplication a(argc, argv);
    Widget w;
    w.showFullScreen();
    w.show();

    return a.exec();
}
