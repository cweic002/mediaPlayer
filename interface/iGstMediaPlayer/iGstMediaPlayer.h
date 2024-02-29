#pragma once
#include "interface/iMediaPlayer/iMediaPlayer.h"
#include <gst/gst.h>

namespace Interface{
    /**
     * @brief Basic interface for creating a GStreamer media player
    */
    class IGstMediaPlayer : virtual public IMediaPlayer {
    public:
        IGstMediaPlayer();
        virtual ~IGstMediaPlayer();
        void play() override ;
        void pause() override ;
        void stop() override ;
        void setPosition(long long int position) override ;
        long long int getDuration()  override ;
        long long int getPosition()  override ;
    protected:
        /**
         * @brief Basic container for conveyor storage
        */
        GstElement * mediaPlayer_;
    };
}
