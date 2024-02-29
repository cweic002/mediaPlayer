#include "iGstVideoPlayer.h"
#include "gst/video/videooverlay.h"

void Interface::IGstVideoPlayer::setVideoOutput(QWidget * output){
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(this->video_),output->winId());
}
