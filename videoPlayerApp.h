#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>

#include "ui_videoPlayerApp.h"

#include "glib.h"
#include "gst/video/videooverlay.h"
#include "gst/video/navigation.h"
#include "gst/video/colorbalance.h"
#include <QTimer>

#include "model/videoPlayer/videoPlayer.h"
#include "controller/init/init.h"
#include "controller/openFile/openFile.h"
#include "controller/player/player.h"
#include "controller/volume/volume.h"
#include "controller/mute/mute.h"
#include "controller/position/position.h"

class QtVideo : public QMainWindow
{
    Q_OBJECT
public:
    QtVideo(QWidget *parent = nullptr);
    ~QtVideo();
    void update_sliderVideoDuration();
Q_SIGNALS:
    void signalFullScreen(bool status);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private slots:
    void on_openFille_triggered();
    void on_pushButtonPlayStop_toggled(bool checked);
    void on_pushButtonSound_toggled(bool checked);
    void on_sliderVideoDuration_valueChanged(int value);
    void on_sliderSoundDuration_valueChanged(int value);
    void on_pushButtonStepDown_clicked();

    void on_pushButtonStepUp_clicked();

private:
    QWidget *menu;
    QTimer *timer;
    Ui::QtVideo ui;
    bool boolFullScreen;
    std::shared_ptr<Model::VideoPlayer> modelVideoPlayer;
    std::unique_ptr<Controller::Init::IInit> controllerInit;
    std::unique_ptr<Controller::OpenFile::IOpenFile> controllerOpenfile;
    std::unique_ptr<Controller::Player::IPlayer> controllerPlayer;
    std::unique_ptr<Controller::Volume::IVolume> controllerVolume;
    std::unique_ptr<Controller::Mute::IMute> controllerMute;
    std::unique_ptr<Controller::Position::IPosition> controllerPosition;
};
