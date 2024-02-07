#include "botomMenuPlayer.h"
#include "ui_botomMenuPlayer.h"
#include <QSignalTransition>

constexpr long long int ns = std::chrono::nanoseconds(1000000).count();

void Widget::BotomMenuPlayer::setPositionTimer(long long int position){
    int ms = position/ns;
    auto pos=QTime(0,0,0,0).addMSecs(ms);
    ui->positionTme->setTime(pos);
}

Widget::BotomMenuPlayer::BotomMenuPlayer(QWidget *parent):duration(0),ui(new Ui::BotomMenuPlayer)
{
    QWidget::setParent(parent);
    ui->setupUi(this);
    //
    auto psm = new QStateMachine();
    //
    auto pStateOn = new QState(psm);
    pStateOn->assignProperty(ui->play_pause,"enabled", true);
    pStateOn->assignProperty(ui->stepDown, "enabled", true);
    pStateOn->assignProperty(ui->stepUp, "enabled", true);
    pStateOn->assignProperty(ui->sliderVideo, "enabled", true);
    //
    auto pStateOff = new QState(psm);
    pStateOff->assignProperty(ui->play_pause,"enabled", false);
    pStateOff->assignProperty(ui->stepDown, "enabled", false);
    pStateOff->assignProperty(ui->stepUp, "enabled", false);
    pStateOff->assignProperty(ui->sliderVideo, "enabled", false);
    pStateOff->assignProperty(ui->sliderVideo, "value", 0);
    //
    QSignalTransition * ptrans1 = pStateOff->addTransition(this, SIGNAL(onActivate()), pStateOn);
    QSignalTransition * ptrans2 = pStateOn->addTransition(this, SIGNAL(offActivate()), pStateOff);
    //
    ptrans1->addAnimation(new QPropertyAnimation(ui->play_pause, "enabled"));
    ptrans1->addAnimation(new QPropertyAnimation(ui->stepDown, "enabled"));
    ptrans1->addAnimation(new QPropertyAnimation(ui->stepUp, "enabled"));
    ptrans1->addAnimation(new QPropertyAnimation(ui->sliderVideo, "enabled"));
    //
    ptrans2->addAnimation(new QPropertyAnimation(ui->play_pause, "enabled"));
    ptrans2->addAnimation(new QPropertyAnimation(ui->stepDown, "enabled"));
    ptrans2->addAnimation(new QPropertyAnimation(ui->stepUp, "enabled"));
    ptrans2->addAnimation(new QPropertyAnimation(ui->sliderVideo, "enabled"));
    ptrans2->addAnimation(new QPropertyAnimation(ui->sliderVideo, "value"));
    //
    psm->setInitialState(pStateOff);
    psm->start();

    connect(ui->play_pause, &QPushButton::toggled, this, &BotomMenuPlayer::playPauseChanged);
    connect(ui->soundOn_Of, &QPushButton::toggled, this, &BotomMenuPlayer::mutedChanged);
    connect(ui->sliderAudio, &QSlider::valueChanged,ui->sliderAudio,[this](int value){
        emit this->volumeChanged((double)ui->sliderAudio->value()/ui->sliderAudio->maximum());
    });
    connect(ui->sliderVideo, &QSlider::valueChanged,ui->sliderVideo,[this](int value){
        auto position = this->duration*ui->sliderVideo->value()/ui->sliderVideo->maximum();
        emit this->positionChanged(position);
        setPositionTimer(position);
    });
}

Widget::BotomMenuPlayer::~BotomMenuPlayer()
{
    delete ui;
}

double Widget::BotomMenuPlayer::getVolume(){
    return (double)ui->sliderAudio->value()/ui->sliderAudio->maximum();
}

void Widget::BotomMenuPlayer::play(){
    ui->play_pause->blockSignals(true);
    ui->play_pause->setChecked(true);
    ui->play_pause->blockSignals(false);
}

void Widget::BotomMenuPlayer::pause(){
    ui->play_pause->blockSignals(true);
    ui->play_pause->setChecked(false);
    ui->play_pause->blockSignals(false);
}

void Widget::BotomMenuPlayer::stop(){
    ui->play_pause->blockSignals(true);
    ui->play_pause->setChecked(false);
    ui->play_pause->blockSignals(false);
}

void Widget::BotomMenuPlayer::setPosition(long long int position){
    setPositionTimer(position);
    if(this->duration>0){
        ui->sliderVideo->blockSignals(true);
        int val = ui->sliderVideo->maximum()*position/this->duration;
        ui->sliderVideo->setSliderPosition(val);
        ui->sliderVideo->blockSignals(false);
    }
}

void Widget::BotomMenuPlayer::setDuration(long long int duration){
    QTime dur(0,0,0,0);
    int ms = duration/ns;
    dur=dur.addMSecs(ms);
    ui->durationTme->setTime(dur);
    this->duration = duration;
}

void Widget::BotomMenuPlayer::setActivate(bool activate){
    qDebug()<<"Widget::BotomMenuPlayer::setActivate:"<<activate<<Qt::endl;
    if(activate){
        emit this->onActivate();
    }else{
        emit this->offActivate();
    }
}
