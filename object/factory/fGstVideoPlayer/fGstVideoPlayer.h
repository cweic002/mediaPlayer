#pragma once

#include "interface/iFactory/iFVideoPlayer/iFVideoPlayer.h"
#include "object/gstVideoPlayer/gstVideoPlayer.h"

namespace Object{
    namespace Factory{
        class FGstVideoPlayer : public Interface::Factory::IFVideoPlayer {
        public:
            Object::GstVideoPlayer * createIVideoPlayer() override;
        };
    }
};
