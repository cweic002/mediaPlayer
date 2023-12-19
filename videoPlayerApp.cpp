#include "videoPlayerApp.h"
#include <QCursor>
#include "controller/init/videoPlayer/videoPlayer.h"
#include "controller/openFile/videoPlayer/videoPlayer.h"
#include "controller/player/videoPlayer/videoPlayer.h"
#include "controller/position/videoPlayer/videoPlayer.h"
#include "controller/volume/videoPlayer/videoPlayer.h"
#include "controller/mute/videoPlayer/videoPlayer.h"
constexpr std::chrono::milliseconds timerInterval = std::chrono::milliseconds(100);
constexpr std::chrono::milliseconds positionIntervalStep = std::chrono::milliseconds(15000);

QtVideo::QtVideo(QWidget* parent):QMainWindow(parent),timer(new QTimer(this)),boolFullScreen(false),
            modelVideoPlayer(new Model::VideoPlayer()),
            controllerPlayer( new Controller::Player::VideoPlayer(modelVideoPlayer,this)),
            controllerInit(new Controller::Init::VideoPlayer(modelVideoPlayer)),
            controllerOpenfile(new Controller::OpenFile::VideoPlayer(modelVideoPlayer)),
            controllerVolume(new Controller::Volume::VideoPlayer(modelVideoPlayer)),
            controllerMute(new Controller::Mute::VideoPlayer(modelVideoPlayer)),
            controllerPosition(new Controller::Position::VideoPlayer(modelVideoPlayer))
{
    ui.setupUi(this);
    controllerInit->init();
    controllerPlayer->init();

    ui.viewVideoPlayer->setModel(modelVideoPlayer);
    ui.viewVideoPlayer->setWindowHandle();
    connect(timer, &QTimer::timeout, this, &QtVideo::update_sliderVideoDuration);
}

void QtVideo::update_sliderVideoDuration(){
    auto pos = controllerPosition->getPosition();
    int position = static_cast<int>(pos*ui.sliderVideoDuration->maximum());
    this->ui.sliderVideoDuration->blockSignals(true);
    ui.sliderVideoDuration->setValue(position);
    this->ui.sliderVideoDuration->blockSignals(false);
}

QtVideo::~QtVideo(){}

//menu
void QtVideo::on_openFille_triggered(){
    QString path = QFileDialog::getOpenFileName(this, tr("Открыть файл"), QDir::currentPath(), tr("*.mkv *.webm *.mp4"));
    if(!path.isEmpty())
    {
        controllerOpenfile->open(path.toUtf8().data());
        //play
        connect(controllerPlayer,&Controller::Player::IPlayer::sendState,[this](Controller::Player::State status){
            this->ui.pushButtonPlayStop->blockSignals(true);
            if(status==Controller::Player::State::PLAYING)
                this->ui.pushButtonPlayStop->setChecked(true);
            else
                this->ui.pushButtonPlayStop->setChecked(false);
            this->ui.pushButtonPlayStop->blockSignals(false);
        });
        controllerPlayer->play(true);
        timer->start(timerInterval);
        //set volume
        gdouble val = (gdouble)ui.sliderSoundDuration->value()/ui.sliderSoundDuration->maximum();
        controllerVolume->setVolume(val);
    }
}

//mouseDoubleClickEvent
void QtVideo::mouseDoubleClickEvent(QMouseEvent *event)
{
    boolFullScreen = !boolFullScreen;
    if(boolFullScreen){
       this->QMainWindow::showFullScreen();
    }else{
        this->QMainWindow::showNormal();
    }
    emit signalFullScreen(boolFullScreen);
}

void QtVideo::on_sliderVideoDuration_valueChanged(int value)
{
    double position = (double)value/ui.sliderVideoDuration->maximum();
    controllerPosition->setPosition(position);
}

void QtVideo::on_sliderSoundDuration_valueChanged(int value)
{
    double volume = (gdouble)value/ui.sliderSoundDuration->maximum();
    controllerVolume->setVolume(volume);
}

void QtVideo::on_pushButtonPlayStop_toggled(bool checked)
{
    if(checked){
        controllerPlayer->play(true);
        timer->start(timerInterval);
    }else{
        controllerPlayer->play(false);
        timer->stop();
    }
}

void QtVideo::on_pushButtonSound_toggled(bool mute)
{
    controllerMute->setMute(mute);
}

void QtVideo::on_pushButtonStepDown_clicked()
{
    controllerPosition->setStep(-positionIntervalStep);
    update_sliderVideoDuration();
    // double pos = controllerPosition->getPosition();
    // int max = ui.sliderVideoDuration->maximum();
    // int position = static_cast<int>(pos*max);
    // update_sliderVideoDuration();
}

void QtVideo::on_pushButtonStepUp_clicked()
{
    controllerPosition->setStep(positionIntervalStep);
    update_sliderVideoDuration();
    // double pos = controllerPosition->getPosition();
    // int max = ui.sliderVideoDuration->maximum();
    // int position = static_cast<int>(pos*max);
    // update_sliderVideoDuration();
}
