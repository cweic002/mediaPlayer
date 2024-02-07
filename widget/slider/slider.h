#pragma once

#include <QSlider>
#include <QDebug>
#include <QMouseEvent>

namespace Widget {
    class Slider : public QSlider
    {
        Q_OBJECT
    public:
        explicit Slider(QWidget *parent = nullptr);
        void mousePressEvent(QMouseEvent *ev)override;
        void mouseMoveEvent(QMouseEvent *ev)override;
    };
}
