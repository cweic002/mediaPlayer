#include "fGstVideoPlayer.h"

Object::GstVideoPlayer * Object::Factory::FGstVideoPlayer::createIVideoPlayer(){
    return new Object::GstVideoPlayer();
}
