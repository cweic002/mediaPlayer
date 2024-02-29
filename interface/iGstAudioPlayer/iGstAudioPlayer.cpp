#pragma once
#include "iGstAudioPlayer.h"


Interface::IGstAudioPlayer::IGstAudioPlayer():audio_(nullptr){};

void Interface::IGstAudioPlayer::setMuted(bool muted){
    if(this->mediaPlayer_ && this->audio_){
        g_object_set(G_OBJECT(this->audio_),"mute",muted, nullptr);
    }
}

void Interface::IGstAudioPlayer::setVolume(double volume){
    if(this->mediaPlayer_ && this->audio_){
        g_object_set(G_OBJECT(this->audio_),"volume",volume, nullptr);
    }
}

double Interface::IGstAudioPlayer::getVolume(){
    double volume = 0;
    if(this->mediaPlayer_ && this->audio_){
        g_object_get(G_OBJECT(this->audio_),"volume",&volume, nullptr);
    }
    return volume;
}
