#include "sliderPlayer.h"

SliderPlayer::SliderPlayer(QWidget* parent):QSlider(parent){
    
}

inline void SliderPlayer::mousePressEvent(QMouseEvent *ev){
    this->setValue((ev->x()*this->maximum())/this->width());
}

inline void SliderPlayer::mouseMoveEvent(QMouseEvent *ev){
    this->setValue((ev->x()*this->maximum())/this->width());
}

void SliderPlayer::setPos(double pos){
    this->blockSignals(true);
    setValue(pos*maximum());
    this->blockSignals(false);
}
