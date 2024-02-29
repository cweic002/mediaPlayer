#pragma once
#include "interface/iAudioPlayer/iAudioPlayer.h"
#include <QWidget>

namespace Interface{
/**
 * @brief Basic interface for creating a video player
 */
struct IVideoPlayer : virtual public IAudioPlayer{
        virtual ~IVideoPlayer() = default;
        /**
         * @brief sets the widget object for the video overlay
         * @param the widget will be used to display video images
        */
        virtual void setVideoOutput(QWidget * output) = 0;
    };
}
