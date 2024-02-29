#pragma once
#include "interface/iVideoPlayer/iVideoPlayer.h"

namespace Interface{
    namespace Factory{
        /**
         * @brief Basic interface factory for creating a video player
        */
        struct IFVideoPlayer{
            /**
             * @brief Creating a video player
             * @return  Return a pointer to Interface::IVideoPlayer
            */
            virtual Interface::IVideoPlayer * createIVideoPlayer() = 0;
        };
    }
};
