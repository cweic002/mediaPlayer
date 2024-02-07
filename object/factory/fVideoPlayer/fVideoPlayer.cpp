#include "fVideoPlayer.h"
#include "object/factory/fGstSrc/fGstSrc.h"
#include "object/factory/fGstDecodebin/fGstDecodebin.h"
#include "object/factory/fGstMyPlaginAudio/fGstMyPlaginAudio.h"
#include "object/factory/fGstMyPlaginVideo/fGstMyPlaginVideo.h"

Object::VideoPlayer * Object::Factory::FVideoPlayer::createIVideoPlayer(){
    return new Object::VideoPlayer(new Object::Factory::FGstSrc(),
                    new Object::Factory::FGstDecodebin(),
                    new Object::Factory::FGstMyPlaginVideo(),
                    new Object::Factory::FGstMyPlaginAudio());
}
