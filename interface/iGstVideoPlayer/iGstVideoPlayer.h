#pragma once
#include "interface/iGstAudioPlayer/iGstAudioPlayer.h"
#include "interface/iVideoPlayer/iVideoPlayer.h"
#include <gst/gst.h>

namespace Interface{
    /**
     * @brief Basic interface for creating a GStreamer video player
    */
    class IGstVideoPlayer : public IGstAudioPlayer, public IVideoPlayer {
    public:
        virtual ~IGstVideoPlayer() = default;
        void setVideoOutput(QWidget * output) override ;
    protected:
        /**
         * @brief video processing pipeline with interface support GST_VIDEO_OVERLAY
        */
        GstElement * video_;
    };
}
