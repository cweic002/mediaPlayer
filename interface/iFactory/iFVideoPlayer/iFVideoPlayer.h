#pragma once
#include "interface/iVideoPlayer/iVideoPlayer.h"

namespace Interface{
    namespace Factory{
        struct IFVideoPlayer{
            virtual Interface::IVideoPlayer * createIVideoPlayer() = 0;
        };
    }
};
