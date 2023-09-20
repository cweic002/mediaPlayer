#include "videoPlayer.h"

GstBusSyncReply VideoPlayer::handle_message(GstBus * bus, GstMessage * message, VideoPlayer * videoPlayer)
{
    switch (GST_MESSAGE_TYPE(message)){
        case GST_MESSAGE_ERROR:{
            GError *err;
            gchar *debug;
            gst_message_parse_error (message, &err, &debug);
            g_print ("Error: %s\n", err->message);
            g_error_free (err);
            g_free (debug);
            break;
        }
        case GST_MESSAGE_STATE_CHANGED: {
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed (message, &old_state, &new_state, &pending_state);
            if (GST_MESSAGE_SRC (message) == GST_OBJECT (videoPlayer->_playbin)) {
                if (new_state == GST_STATE_PLAYING) {
                    videoPlayer->timer.start();
                }else if(new_state == GST_STATE_PAUSED){
                    videoPlayer->timer.pause();
                }
            }
            break;
        }
        case GST_MESSAGE_STREAM_START: {
            gst_element_query_duration(videoPlayer->_playbin, GST_FORMAT_TIME, &videoPlayer->_duration);
            break;
        }
        default:
            break;
    }
    gst_message_unref(message);
    return GST_BUS_DROP;
}

void VideoPlayer::includeWatch(){
    auto bus = gst_element_get_bus(_playbin);
    gst_bus_set_sync_handler(bus,(GstBusSyncHandler)handle_message,this,NULL);
    gst_object_unref(bus);
}

VideoPlayer::VideoPlayer(QWidget * parent):
                QWidget(parent),
                _playbin(gst_element_factory_make("playbin", "playbin")),
                _duration(0),
                _position(0),
                timer(gst_pipeline_get_clock((GstPipeline*)_playbin)){
    if(!_playbin){
        throw PlayerException("Not all elements could be created");
    }
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(_playbin),this->winId());

    includeWatch();
    connect(&timer,&Timer::timeout,this,&VideoPlayer::updatePosition);

    int flags = 0;
    g_object_get(_playbin, "flags", &flags, NULL);
    flags &= ~PlayFlags::PLAY_FLAG_TEXT;
    g_object_set(_playbin, "flags", flags, NULL);
}

VideoPlayer::~VideoPlayer(){
    gst_element_set_state(_playbin, GST_STATE_NULL);
    gst_object_unref(_playbin);
}

bool VideoPlayer::openFile(const char * path){
    if(_playbin){
        gst_element_set_state(_playbin, GST_STATE_NULL);
        g_object_set(_playbin, "uri",path, NULL);
        return true;
    }
    return false;
}

bool VideoPlayer::play(){
    if(_playbin){
        GstStateChangeReturn state = gst_element_set_state(_playbin,GST_STATE_PLAYING);
        bool status = state != GST_STATE_CHANGE_FAILURE;
        emit watchPlay(status);
        return status;
    }
    return false;
}

bool VideoPlayer::pause(){
    emit watchPlay(false);
    if(_playbin){
         GstStateChangeReturn state = gst_element_set_state(_playbin,GST_STATE_PAUSED);
         return state != GST_STATE_CHANGE_FAILURE;
    }
    return false;
}

void VideoPlayer::stop(){

}

bool VideoPlayer::addStepUp(long long step){
    if(_playbin){
        auto tempPosition = _position + step;
        _position = tempPosition < _duration ? tempPosition > 0 ? tempPosition: 0: _duration;
        return gst_element_seek_simple(_playbin, GST_FORMAT_TIME,
            (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH), _position);
    }
    return false;
}

bool VideoPlayer::addStepDown(long long step){
    if(_playbin){
        auto tempPosition = _position - step;
        _position = tempPosition < _duration ? tempPosition > 0 ? tempPosition: 0: _duration;
        return gst_element_seek_simple(_playbin, GST_FORMAT_TIME,
            (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH), _position);
    }
    return false;
}

void VideoPlayer::setMute(bool mute){
    if(_playbin){
        g_object_set(G_OBJECT(_playbin),"mute",mute, NULL);
    }
}

void VideoPlayer::setVolume(double volume){
    if(_playbin){
        g_object_set(G_OBJECT(_playbin), "volume",volume, NULL);
    }
}

long long VideoPlayer::getDuration(){
    return _duration;
}

long long VideoPlayer::getPosition(){
    gst_element_query_position (_playbin,GST_FORMAT_TIME,&_position);
    return _position;
}

void VideoPlayer::updatePosition(){
    gst_element_query_position(_playbin,GST_FORMAT_TIME,&_position);
    auto position = (double)_position/_duration;
    emit watchPosition(position);
    if( _position == _duration){
        timer.pause();
    }
}

void VideoPlayer::setPosition(long long position){
    if(_playbin){
        gst_element_seek_simple(_playbin, GST_FORMAT_TIME,
            (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH),position);
    }
}

void VideoPlayer::play(bool status){
    if(status){
        this->play();
    }else{
        this->pause();
    }
}


