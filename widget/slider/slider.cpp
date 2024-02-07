#include "slider.h"

Widget::Slider::Slider(QWidget* parent):QSlider(parent){}

void Widget::Slider::mousePressEvent(QMouseEvent *ev){
    this->setValue((ev->x()*this->maximum())/this->width());
}

void Widget::Slider::mouseMoveEvent(QMouseEvent *ev){
    this->setValue((ev->x()*this->maximum())/this->width());
}
