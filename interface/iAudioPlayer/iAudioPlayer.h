#pragma once
#include "interface/iMediaPlayer/iMediaPlayer.h"

namespace Interface{
    /**
     * @brief Basic interface for creating an audio player
    */
    struct IAudioPlayer : virtual public IMediaPlayer{
        virtual ~IAudioPlayer() = default;
        /**
         * @brief Turn sound on or off
         * @param Muted bool true or false
        */
        virtual void setMuted(bool muted) = 0;
        /**
         * @brief Set volume
         * @param Volume takes range from 0.0 to 1.0
        */
        virtual void setVolume(double volume) = 0;
        /**
         * @brief Get volume
         * @return Returns volume in the range from 0.0 to 1.0
         */
        virtual double getVolume() = 0;
    };
}
