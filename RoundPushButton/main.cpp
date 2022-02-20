#include "roundpushbutton.h"
#include <QApplication>
#include <QDebug>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    /* 不支持gif动态头像显示模式 */
    RoundPushButton w;
    w.setMinimumSize(100,100);
    w.setIcon("D:/GitHub/QtCustomerWidgets/Resource/R-C.gif");
    w.setRadius(50);
    QObject::connect(&w,&RoundPushButton::clicked,[=](){
        qDebug() << "RoundPushButton clicked." << Qt::endl;
    });
    QTimer::singleShot(2000,&a,[&w](){
        w.setIcon("D:/GitHub/QtCustomerWidgets/Resource/sss.gif");
    });
    w.show();


    /* 支持gif动态头像显示模式 */
    QString fileName("D:/GitHub/QtCustomerWidgets/Resource/R-C.gif");
    GifRoundPushButton Gifw(fileName);
    Gifw.setFixedSize(100,100);
    QObject::connect(&Gifw,&GifRoundPushButton::clicked,[=](){
        qDebug() << "GifRoundPushButton clicked." << Qt::endl;
    });
    Gifw.setIcon(fileName);
    Gifw.setStyleSheet("QPushButton{font-size:100px;color:yellow;border-style:solid;border-width:1px;border-color:black;border-radius:150px;}");
    Gifw.show();

    return a.exec();
}
