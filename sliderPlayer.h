#ifndef SLIDERPLAYER_H
#define SLIDERPLAYER_H
#include <QSlider>
#include <QDebug>
#include <QMouseEvent>

class SliderPlayer : public QSlider
{
    Q_OBJECT
public slots:
    void setPos(double pos);
public:
    explicit SliderPlayer(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *ev)override;
    void mouseMoveEvent(QMouseEvent *ev)override;
};

#endif // SLIDERPLAYER_H
