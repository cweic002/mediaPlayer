#include "iGstMediaPlayer.h"

Interface::IGstMediaPlayer::IGstMediaPlayer():mediaPlayer_(nullptr){}

Interface::IGstMediaPlayer::~IGstMediaPlayer(){
    if(this->mediaPlayer_){
        gst_element_set_state(this->mediaPlayer_, GST_STATE_NULL);
        gst_object_unref(this->mediaPlayer_);
    }
}

void Interface::IGstMediaPlayer::play(){
    if(this->mediaPlayer_){
        gst_element_set_state(this->mediaPlayer_, GST_STATE_PLAYING);
    }
}

void Interface::IGstMediaPlayer::pause(){
    if(this->mediaPlayer_){
        gst_element_set_state(this->mediaPlayer_, GST_STATE_PAUSED);
    }
}

void Interface::IGstMediaPlayer::stop(){
    if(this->mediaPlayer_){
        gst_element_set_state(this->mediaPlayer_, GST_STATE_READY);
    }
}

gint64 Interface::IGstMediaPlayer::getDuration(){
    gint64 duration = 0;
    if(this->mediaPlayer_){
        gst_element_query_duration(this->mediaPlayer_, GST_FORMAT_TIME, &duration);
    }
    return duration;
}

void Interface::IGstMediaPlayer::setPosition(gint64 position){
    if(this->mediaPlayer_){
        gst_element_seek_simple(this->mediaPlayer_, GST_FORMAT_TIME,
                                (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH),position);
    }
}

gint64 Interface::IGstMediaPlayer::getPosition(){
    gint64 position = 0;
    if(this->mediaPlayer_){
        gst_element_query_position(this->mediaPlayer_,GST_FORMAT_TIME,&position);
    }
    return position;
}
