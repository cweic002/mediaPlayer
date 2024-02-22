#include "fVideoPlayer.h"
#include "object/factory/fGstSrc/fGstSrc.h"
#include "object/factory/fGstDecodebin/fGstDecodebin.h"
#include "object/factory/fGstMyPlaginAudio/fGstMyPlaginAudio.h"
#include "object/factory/fGstMyPlaginVideo/fGstMyPlaginVideo.h"

Object::VideoPlayer * Object::Factory::FVideoPlayer::createIVideoPlayer(){
    return new Object::VideoPlayer(Object::Factory::FGstSrc().createGstElement(),
                    Object::Factory::FGstDecodebin().createGstElement(),
                    Object::Factory::FGstMyPlaginVideo().createGstVideoOverlay(),
                    Object::Factory::FGstMyPlaginAudio().createGstElement());
}
