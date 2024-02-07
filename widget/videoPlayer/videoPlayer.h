#pragma once

#include "interface/videoPlayer/videoPlayer.h"
#include "interface/botomMenu/player/player.h"
#include "qtimer.h"

namespace Ui {
class VideoPlayer;
}

namespace Widget {
class VideoPlayer : public QWidget,public Interface::IPlayer{
        Q_OBJECT
        Interface::IVideoPlayer * _videoPlayer;
        QTimer _timer;
    public:
        VideoPlayer(Interface::IVideoPlayer * videoPlayer,QWidget * parent = nullptr);
        void setBotomMenuPlayer(Interface::IBotomMenuPlayer * botomMenuPlayer);
        void pause(){};
        void play(){};
        void stop(){};
        void setMedia(const QString & path){};
        long long int getDuration(){return 1;};
        void setPosition(long long int position){};
        long long int getPosition(){return 1;};
        ~VideoPlayer();
    private:
        Ui::VideoPlayer *ui;
    };
}
