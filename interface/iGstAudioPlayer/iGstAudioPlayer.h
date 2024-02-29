#pragma once
#include "interface/iAudioPlayer/iAudioPlayer.h"
#include "interface/iGstMediaPlayer/iGstMediaPlayer.h"

namespace Interface{
    /**
     * @brief Basic interface for creating a GStreamer audio player
    */
    class IGstAudioPlayer : public IGstMediaPlayer, virtual public IAudioPlayer {
    public:
        IGstAudioPlayer();
        virtual ~IGstAudioPlayer() = default;
        void setMuted(bool muted) override;
        void setVolume(double volume) override;
        double getVolume() override;
    protected:
        /**
         * @brief audio processing pipeline with interface support GstStreamVolume
        */
        GstElement * audio_;
    };
}
