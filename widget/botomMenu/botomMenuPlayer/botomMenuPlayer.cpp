#include "botomMenuPlayer.h"
#include "ui_botomMenuPlayer.h"
#include <QSignalTransition>

constexpr long long int ns = std::chrono::nanoseconds(1000000).count();

void Widget::BotomMenuPlayer::setPositionTimer(long long int position){
    int ms = position/ns;
    auto pos=QTime(0,0,0,0).addMSecs(ms);
    ui_->positionTme->setTime(pos);
}

Widget::BotomMenuPlayer::BotomMenuPlayer(QWidget *parent):duration_(0),ui_(new Ui::BotomMenuPlayer)
{
    QWidget::setParent(parent);
    ui_->setupUi(this);
    //
    auto psm = new QStateMachine();
    //
    auto pStateOn = new QState(psm);
    pStateOn->assignProperty(ui_->play_pause,"enabled", true);
    pStateOn->assignProperty(ui_->stepDown, "enabled", true);
    pStateOn->assignProperty(ui_->stepUp, "enabled", true);
    pStateOn->assignProperty(ui_->sliderVideo, "enabled", true);
    //
    auto pStateOff = new QState(psm);
    pStateOff->assignProperty(ui_->play_pause,"enabled", false);
    pStateOff->assignProperty(ui_->stepDown, "enabled", false);
    pStateOff->assignProperty(ui_->stepUp, "enabled", false);
    pStateOff->assignProperty(ui_->sliderVideo, "enabled", false);
    pStateOff->assignProperty(ui_->sliderVideo, "value", 0);
    //
    QSignalTransition * ptrans1 = pStateOff->addTransition(this, SIGNAL(onActivate()), pStateOn);
    QSignalTransition * ptrans2 = pStateOn->addTransition(this, SIGNAL(offActivate()), pStateOff);
    //
    ptrans1->addAnimation(new QPropertyAnimation(ui_->play_pause, "enabled"));
    ptrans1->addAnimation(new QPropertyAnimation(ui_->stepDown, "enabled"));
    ptrans1->addAnimation(new QPropertyAnimation(ui_->stepUp, "enabled"));
    ptrans1->addAnimation(new QPropertyAnimation(ui_->sliderVideo, "enabled"));
    //
    ptrans2->addAnimation(new QPropertyAnimation(ui_->play_pause, "enabled"));
    ptrans2->addAnimation(new QPropertyAnimation(ui_->stepDown, "enabled"));
    ptrans2->addAnimation(new QPropertyAnimation(ui_->stepUp, "enabled"));
    ptrans2->addAnimation(new QPropertyAnimation(ui_->sliderVideo, "enabled"));
    ptrans2->addAnimation(new QPropertyAnimation(ui_->sliderVideo, "value"));
    //
    psm->setInitialState(pStateOff);
    psm->start();

    connect(ui_->play_pause, &QPushButton::toggled, this, &BotomMenuPlayer::playPauseChanged);
    connect(ui_->soundOn_Of, &QPushButton::toggled, this, &BotomMenuPlayer::mutedChanged);
    connect(ui_->sliderAudio, &QSlider::valueChanged,ui_->sliderAudio,[this](int value){
        emit this->volumeChanged((double)ui_->sliderAudio->value()/ui_->sliderAudio->maximum());
    });
    connect(ui_->sliderVideo, &QSlider::valueChanged,ui_->sliderVideo,[this](int value){
        auto position = this->duration_*ui_->sliderVideo->value()/ui_->sliderVideo->maximum();
        emit this->positionChanged(position);
        setPositionTimer(position);
    });
}

Widget::BotomMenuPlayer::~BotomMenuPlayer()
{
    delete ui_;
}

double Widget::BotomMenuPlayer::getVolume(){
    return (double)ui_->sliderAudio->value()/ui_->sliderAudio->maximum();
}

void Widget::BotomMenuPlayer::play(){
    ui_->play_pause->blockSignals(true);
    ui_->play_pause->setChecked(true);
    ui_->play_pause->blockSignals(false);
}

void Widget::BotomMenuPlayer::pause(){
    ui_->play_pause->blockSignals(true);
    ui_->play_pause->setChecked(false);
    ui_->play_pause->blockSignals(false);
}

void Widget::BotomMenuPlayer::stop(){
    ui_->play_pause->blockSignals(true);
    ui_->play_pause->setChecked(false);
    ui_->play_pause->blockSignals(false);
}

void Widget::BotomMenuPlayer::setPosition(long long int position){
    setPositionTimer(position);
    if(this->duration_>0){
        ui_->sliderVideo->blockSignals(true);
        int val = ui_->sliderVideo->maximum()*position/this->duration_;
        ui_->sliderVideo->setSliderPosition(val);
        ui_->sliderVideo->blockSignals(false);
    }
}

void Widget::BotomMenuPlayer::setDuration(long long int duration_){
    QTime dur(0,0,0,0);
    int ms = duration_/ns;
    dur=dur.addMSecs(ms);
    ui_->durationTme->setTime(dur);
    this->duration_ = duration_;
}

void Widget::BotomMenuPlayer::setActivate(bool activate){
    qDebug()<<"Widget::BotomMenuPlayer::setActivate:"<<activate<<Qt::endl;
    if(activate){
        emit this->onActivate();
    }else{
        emit this->offActivate();
    }
}
