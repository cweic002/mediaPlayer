#include "videoPlayerApp.h"
#include <QtWidgets/QApplication>
#include <QtWidgets>
#include <gst/gst.h>

#include "widget/botomMenu/botomMenuPlayer/botomMenuPlayer.h"
#include "object/factory/fGstVideoPlayer/fGstVideoPlayer.h"
#include <QMessageBox>

void connectVideoPlayerBotomMenuPlayer(Object::GstVideoPlayer * videoPlayer,Widget::BotomMenuPlayer * botomMenuPlayer){
    QObject::connect(botomMenuPlayer,&Interface::IBotomMenuPlayer::playPauseChanged,botomMenuPlayer,[videoPlayer](bool play){
        if(play){
            videoPlayer->play();
        }else{
            videoPlayer->pause();
        }
    });
    QObject::connect(botomMenuPlayer,&Interface::IBotomMenuPlayer::mutedChanged,[videoPlayer](bool muted){
        videoPlayer->setMuted(muted);
    });
    QObject::connect(botomMenuPlayer,&Interface::IBotomMenuPlayer::positionChanged,[videoPlayer](long long int position){
        videoPlayer->setPosition(position);
    });
    QObject::connect(botomMenuPlayer,&Interface::IBotomMenuPlayer::volumeChanged,[videoPlayer](double volume){
        videoPlayer->setVolume(volume);
    });
    QObject::connect(videoPlayer,&Object::GstVideoPlayer::stateChanged,videoPlayer,[botomMenuPlayer](Object::GstVideoPlayer::State state){
        switch(state){
        case Object::GstVideoPlayer::State::PlayingState : {
            botomMenuPlayer->play();
            break;
        }
        case Object::GstVideoPlayer::State::PausedState : {
            botomMenuPlayer->pause();
            break;
        }
        case Object::GstVideoPlayer::State::StoppedState : {
            botomMenuPlayer->stop();
            break;
        }
        }
    });
    QObject::connect(videoPlayer,&Object::GstVideoPlayer::mediaStatusChanged,videoPlayer,[videoPlayer,botomMenuPlayer](Object::GstVideoPlayer::MediaStatus mediaStatus){
        switch(mediaStatus){
        case Object::GstVideoPlayer::MediaStatus::UnknownMediaStatus :
        case Object::GstVideoPlayer::MediaStatus::NoMedia:
        case Object::GstVideoPlayer::MediaStatus::InvalidMedia :{
            videoPlayer->stop();
            botomMenuPlayer->setActivate(false);
            break;
        }
        case Object::GstVideoPlayer::MediaStatus::EndOfMedia : {
            videoPlayer->pause();
            break;
        }
        default:{
            botomMenuPlayer->setActivate(true);
            return;
        }
        }
    });
    QObject::connect(videoPlayer,&Object::GstVideoPlayer::durationChanged,botomMenuPlayer,&Interface::IBotomMenuPlayer::setDuration);
    QObject::connect(videoPlayer,&Object::GstVideoPlayer::positionChanged,botomMenuPlayer,&Interface::IBotomMenuPlayer::setPosition);
}


int main(int argc, char* argv[]) {
    if (!g_thread_supported())
        g_thread_init(nullptr);
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
        auto * videoPlayer = Object::Factory::FGstVideoPlayer().createIVideoPlayer();
        Widget::BotomMenuPlayer * botomMenuPlayer = new Widget::BotomMenuPlayer();
        QtVideo window(&app,
                       videoPlayer,
                       botomMenuPlayer);
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





