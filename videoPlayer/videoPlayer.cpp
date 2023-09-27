#include "videoPlayer.h"

VideoPlayer::VideoPlayer(QWidget * parent):QWidget(parent),
    VideoPlayer::PlaybinGstream([&](){
            gst_element_query_position(playbin, GST_FORMAT_TIME, &position);
            auto tempPosition = (double)position /duration;
            emit this->watchPosition(tempPosition);
            if (tempPosition == duration){
                this->pause();
            }
        })
{
    PlaybinGstream::setWindowHandle(this->winId());
}

bool VideoPlayer::play(){
    auto res = PlaybinGstream::play();
    emit watchPlay(res);
    return res;
}

bool VideoPlayer::pause(){
    auto res = PlaybinGstream::pause();
    emit watchPlay(false);
    return res;
}

void VideoPlayer::setPlay(bool play){
    if(play){
        PlaybinGstream::play();
    }else{
        PlaybinGstream::pause();
    }
}

void VideoPlayer::setMute(bool mute){
    PlaybinGstream::setMute(mute);
}



