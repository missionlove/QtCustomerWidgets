#ifndef ROUNDPUSHBUTTON_H
#define ROUNDPUSHBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QPixmap>
#include <QMovie>
#include <QLabel>
#include <QPainter>
#include <QDebug>

class AntialiasingMovieLabel:public QLabel
{
public:
     void paintEvent(QPaintEvent *)
     {
         if (this->movie() && this->movie()->isValid())
         {
             QPainter painter(this);
             painter.setRenderHint(QPainter::HighQualityAntialiasing, true);
             painter.setCompositionMode(QPainter::CompositionMode_Source);//覆盖模式
             QPixmap curr_pix = this->movie()->currentPixmap();
             if (this->hasScaledContents())
             {
                 QPixmap pix = curr_pix.scaled( QSize(50,50) /*this->size()*/,
                                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                 /// 绘制成圆形

                 //绘画路径
                 QPainterPath path;
                 path.addEllipse(this->rect().center(),50,50);
                 painter.setClipPath(path);
                 //绘图
                 //painter.drawPixmap(this->rect(),scaledPixmap);

                 painter.drawPixmap(QPoint(0, 0), pix);
             }
             else
             {
                 /// 绘制成圆形

                 //绘画路径
                 QPainterPath path;
                 path.addEllipse(this->rect().center(),50,50);
                 painter.setClipPath(path);

                 painter.drawPixmap(QPoint(0, 0), curr_pix);
             }
         }
     }
};

class GifRoundPushButton:public QPushButton
{
    Q_OBJECT
public:
    GifRoundPushButton(QString icon = QString(),QPushButton *parent = nullptr);
    void setIcon(const QString& icon);
    virtual void paintEvent(QPaintEvent *event);
private:
    QString iconName;
    QMovie* m_movie;
    AntialiasingMovieLabel* label;
};




class RoundPushButton : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(int _radius READ radius WRITE setRadius NOTIFY radiusChanged)
public:
    RoundPushButton(QPushButton *parent = nullptr);
    ~RoundPushButton();
    virtual void paintEvent(QPaintEvent *event);

    int radius();
    void setRadius(int radius);

    void setIcon(const QString &icon);
signals:
    void radiusChanged();
private:
    int _radius;
    QPixmap _pixmap;
};
#endif // ROUNDPUSHBUTTON_H
