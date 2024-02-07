#pragma once

#include "interface/iFactory/iFVideoPlayer/iFVideoPlayer.h"
#include "object/videoPlayer/videoPlayer.h"

namespace Object{
    namespace Factory{
        class FVideoPlayer : public Interface::Factory::IFVideoPlayer {
        public:
            Object::VideoPlayer * createIVideoPlayer() override;
        };
    }
};
