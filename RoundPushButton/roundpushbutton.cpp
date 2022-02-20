#include "roundpushbutton.h"
#include <QPainter>
#include <QMovie>
#include <QHBoxLayout>

RoundPushButton::RoundPushButton(QPushButton *parent)
    : QPushButton(parent)
{


}

RoundPushButton::~RoundPushButton()
{
}



void RoundPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    //抗锯齿
    painter.setRenderHints(QPainter::HighQualityAntialiasing/*Antialiasing*/ | QPainter::SmoothPixmapTransform);

    // 图片缩放
    QPixmap scaledPixmap =  _pixmap.scaled(width(),height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //绘画路径
    QPainterPath path;
    path.addEllipse(this->rect().center(),_radius,_radius);
    painter.setClipPath(path);
    //绘图
    painter.drawPixmap(this->rect(),scaledPixmap);

}

int RoundPushButton::radius()
{
    return _radius;
}

void RoundPushButton::setRadius(int radius)
{
    this->_radius = radius;
}

void RoundPushButton::setIcon(const QString &icon)
{
    if(_pixmap.load(icon))
    {
        qDebug("load icon ok.");
        update();
    }
}


/*************************************************************************/
GifRoundPushButton::GifRoundPushButton(QString icon, QPushButton *parent)
    :iconName(icon),QPushButton(parent)
{
    label = new AntialiasingMovieLabel;
    m_movie = new QMovie;
    QVBoxLayout* vlayout = new QVBoxLayout;
    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addStretch();
    hlayout->addWidget(label);
    hlayout->addStretch();

    hlayout->setContentsMargins(0,0,0,0);
    hlayout->setSpacing(0);

    vlayout->addStretch();
    vlayout->addLayout(hlayout);
    vlayout->addStretch();
    setLayout(vlayout);
    vlayout->setContentsMargins(0,0,0,0);
    vlayout->setSpacing(0);

}

void GifRoundPushButton::setIcon(const QString &icon)
{
    iconName = icon;
    m_movie->setFileName(iconName);

    // QSize si(size());
    // m_movie->setScaledSize(QSize(70,70));

    label->setMovie(m_movie);
    m_movie->start();

    label->setFrameShape (QFrame::Box);
    label->setStyleSheet("border-width: 1px;"
                          "border-style: solid;"
                          "border-radius:50;"
                          "border-color: rgb(255, 170, 0);");
}

/// 绘制蒙版
void GifRoundPushButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
#if 0
    QPainter painter(this);
    painter.setBackground(QBrush(Qt::black));

    //抗锯齿
    painter.setRenderHints(QPainter::HighQualityAntialiasing/*Antialiasing*/ | QPainter::SmoothPixmapTransform);

    // 绘制蒙版
    QPixmap _pixmap;
    _pixmap.load("D:/GitHub/QtCustomerWidgets/Resource/head_mask.jpg");
    QPixmap scaledPixmap =  _pixmap.scaled(width(),height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    //绘画路径
    QPainterPath path;
    path.addEllipse(this->rect().center(),50,50);
    painter.setClipPath(path);
    //绘图
    painter.drawPixmap(this->rect(),scaledPixmap);
#endif
}
