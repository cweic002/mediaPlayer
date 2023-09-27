#include "playbinGstream.h"
#include "gst/video/videooverlay.h"

GstBusSyncReply PlaybinGstream::handle_message(GstBus* bus, GstMessage* message, PlaybinGstream * playbinGstream)
{
    switch (GST_MESSAGE_TYPE(message)){
    case GST_MESSAGE_ERROR: {
        GError* err;
        gchar* debug;
        gst_message_parse_error(message, &err, &debug);
        g_print("Error: %s\n", err->message);
        g_error_free(err);
        g_free(debug);
        break;
    }
    case GST_MESSAGE_STATE_CHANGED: {
        GstState old_state, new_state, pending_state;
        gst_message_parse_state_changed(message, &old_state, &new_state, &pending_state);
        if (GST_MESSAGE_SRC(message) == GST_OBJECT(playbinGstream->playbin)) {
            if (new_state == GST_STATE_PLAYING){
                if(!playbinGstream->isPlay){
                    playbinGstream->isPlay = true;
                    if(playbinGstream->callBackPlay){
                        (*playbinGstream->callBackPlay)();
                    }
                    playbinGstream->timer.start();
                }
            }
            else if (new_state == GST_STATE_PAUSED) {
                if(playbinGstream->isPlay){
                    playbinGstream->isPlay = false;
                    if(playbinGstream->callBackPlay){
                        (*playbinGstream->callBackPlay)();
                    }
                    playbinGstream->timer.pause();
                }
            }
        }
        break;
    }
    case GST_MESSAGE_STREAM_START: {
        gst_element_query_duration(playbinGstream->playbin, GST_FORMAT_TIME, &playbinGstream->duration);
        break;
    }
    default:
        break;
    }
    gst_message_unref(message);
    return GST_BUS_DROP;
}

PlaybinGstream::~PlaybinGstream() {
    gst_element_set_state(playbin, GST_STATE_NULL);
    gst_object_unref(playbin);
}

void PlaybinGstream::updatePosition() {
    gst_element_query_position(playbin, GST_FORMAT_TIME, &position);
    auto tempPosition = (double)position /duration;
    if (tempPosition == duration) {
        timer.pause();
    }
}

void PlaybinGstream::stop(){
    
}

bool PlaybinGstream::openFile(const char * path){
    if(playbin){
        gst_element_set_state(playbin, GST_STATE_NULL);
        g_object_set(playbin, "uri",path, NULL);
        return true;
    }
    return false;
}

bool PlaybinGstream::play(){
    if(playbin){
        GstStateChangeReturn state = gst_element_set_state(playbin,GST_STATE_PLAYING);
        bool status = state != GST_STATE_CHANGE_FAILURE;
        return status;
    }
    return false;
}

bool PlaybinGstream::pause(){
    if(playbin){
         GstStateChangeReturn state = gst_element_set_state(playbin,GST_STATE_PAUSED);
         return state != GST_STATE_CHANGE_FAILURE;
    }
    return false;
}

bool PlaybinGstream::addStepUp(gint64 step){
    if(playbin){
        auto tempPosition = position + step;
        position = tempPosition <duration ? tempPosition > 0 ? tempPosition: 0: duration;
        return gst_element_seek_simple(playbin, GST_FORMAT_TIME,
            (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH),position);
    }
    return false;
}

bool PlaybinGstream::addStepDown(gint64 step){
    if(playbin){
        auto tempPosition = position - step;
        position = tempPosition < duration ? tempPosition > 0 ? tempPosition: 0: duration;
        return gst_element_seek_simple(playbin, GST_FORMAT_TIME,
            (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH), position);
    }
    return false;
}

void PlaybinGstream::setMute(bool mute){
    if(playbin){
        g_object_set(G_OBJECT(playbin),"mute",mute, NULL);
    }
}

void PlaybinGstream::setVolume(double volume){
    if(playbin){
        g_object_set(G_OBJECT(playbin), "volume",volume, NULL);
    }
}

gint64 PlaybinGstream::getDuration(){
    return duration;
}

gint64 PlaybinGstream::getPosition(){
    gst_element_query_position (playbin,GST_FORMAT_TIME,&position);
    return position;
}

void PlaybinGstream::setPosition(gint64 position){
    if(playbin){
        gst_element_seek_simple(playbin, GST_FORMAT_TIME,
            (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH),position);
    }
}

void PlaybinGstream::setWindowHandle(guintptr handle){
    if(playbin){
        gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(playbin),handle);
    }
}

