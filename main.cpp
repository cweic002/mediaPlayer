#include "videoPlayerApp.h"
#include <QtWidgets/QApplication>
#include <QtWidgets>
#include <gst/gst.h>

#include "object/videoPlayer/videoPlayer.h"
#include "widget/botomMenu/botomMenuPlayer/botomMenuPlayer.h"
#include "object/factory/fVideoPlayer/fVideoPlayer.h"
#include <QMessageBox>

void connectVideoPlayerBotomMenuPlayer(Object::VideoPlayer * videoPlayer,Widget::BotomMenuPlayer * botomMenuPlayer){
    QObject::connect(botomMenuPlayer,&Interface::IBotomMenuPlayer::playPauseChanged,botomMenuPlayer,[videoPlayer](bool play){
        if(play){
            videoPlayer->play();
        }else{
            videoPlayer->pause();
        }
    });
    QObject::connect(botomMenuPlayer,&Interface::IBotomMenuPlayer::mutedChanged,videoPlayer,&Object::VideoPlayer::setMuted);
    QObject::connect(botomMenuPlayer,&Interface::IBotomMenuPlayer::positionChanged,videoPlayer,&Object::VideoPlayer::setPosition);
    QObject::connect(botomMenuPlayer,&Interface::IBotomMenuPlayer::volumeChanged,videoPlayer,&Object::VideoPlayer::setVolume);
    QObject::connect(videoPlayer,&Object::VideoPlayer::stateChanged,videoPlayer,[botomMenuPlayer](Object::VideoPlayer::State state){
        switch(state){
        case Object::VideoPlayer::State::PlayingState : {
            botomMenuPlayer->play();
            break;
        }
        case Object::VideoPlayer::State::PausedState : {
            botomMenuPlayer->pause();
            break;
        }
        case Object::VideoPlayer::State::StoppedState : {
            botomMenuPlayer->stop();
            break;
        }
        }
    });
    QObject::connect(videoPlayer,&Object::VideoPlayer::mediaStatusChanged,videoPlayer,[videoPlayer,botomMenuPlayer](Object::VideoPlayer::MediaStatus mediaStatus){
        switch(mediaStatus){
        case Object::VideoPlayer::MediaStatus::UnknownMediaStatus :
        case Object::VideoPlayer::MediaStatus::NoMedia:
        case Object::VideoPlayer::MediaStatus::InvalidMedia :{
            videoPlayer->stop();
            botomMenuPlayer->setActivate(false);
            break;
        }
        case Object::VideoPlayer::MediaStatus::EndOfMedia : {
            videoPlayer->pause();
            break;
        }
        default:{
            botomMenuPlayer->setActivate(true);
            return;
        }
        }
    });
    QObject::connect(videoPlayer,&Object::VideoPlayer::durationChanged,botomMenuPlayer,&Interface::IBotomMenuPlayer::setDuration);
    QObject::connect(videoPlayer,&Object::VideoPlayer::positionChanged,botomMenuPlayer,&Interface::IBotomMenuPlayer::setPosition);
}

int main(int argc, char* argv[]) {
    if (!g_thread_supported())
        g_thread_init(NULL);
    gst_init(&argc, &argv);
    QApplication app(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString & locale : uiLanguages) {
        const QString baseName = "videoPlayerApp_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)){
            qDebug() << baseName <<Qt::endl;
            app.installTranslator(&translator);
            break;
        }
    }
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    try{
        Object::VideoPlayer * videoPlayer = Object::Factory::FVideoPlayer().createIVideoPlayer();
        QtVideo window(&app,videoPlayer,
                       new Widget::BotomMenuPlayer(),
                       connectVideoPlayerBotomMenuPlayer);
        window.show();
        return app.exec();
    }catch (const std::exception& err){
        int n = QMessageBox::critical(0,
                QtVideo::tr("Error"),QtVideo::tr("Error plugin gstreamer"),
                QMessageBox::StandardButton::Ok);
        if (n == QMessageBox::Ok){
            return EXIT_FAILURE;
        }
    }
}





