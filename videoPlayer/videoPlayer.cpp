#include "videoPlayer.h"

#include "glib.h"
#include "gst/gst.h"
#include "gst/video/videooverlay.h"
#include "gst/video/navigation.h"
#include "gst/video/colorbalance.h"
#include "player/playerException.h"

#include "timer/timer.h"

struct PlayerObj;
GstBusSyncReply handle_message(GstBus* bus, GstMessage* message, PlayerObj* playerObj);

struct PlayerObj {
    enum PlayFlags {
        PLAY_FLAG_VIDEO = (1 << 0),
        PLAY_FLAG_AUDIO = (1 << 1),
        PLAY_FLAG_TEXT = (1 << 2)
    };
    GstElement* playbin;
    gint64 duration;
    gint64 position;
    Timer timer;
    VideoPlayer * videoPlayer;
    PlayerObj(VideoPlayer * videoPlayer) :videoPlayer(videoPlayer),
            playbin(gst_element_factory_make("playbin", "playbin")),
            duration(0),
            position(0),
            timer(gst_pipeline_get_clock((GstPipeline*)playbin), (GstClockCallback)sendSignal, this){
        auto bus = gst_element_get_bus(playbin);
        gst_bus_set_sync_handler(bus, (GstBusSyncHandler)handle_message,this, NULL);
        gst_object_unref(bus);
        if (!playbin) {
            throw PlayerException("Not all elements could be created");
        }
        gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(playbin), videoPlayer->winId());

        int flags = 0;
        g_object_get(playbin, "flags", &flags, NULL);
        flags &= ~PlayFlags::PLAY_FLAG_TEXT;
        g_object_set(playbin, "flags", flags, NULL);
    }
    virtual ~PlayerObj() {
        gst_element_set_state(playbin, GST_STATE_NULL);
        gst_object_unref(playbin);
    }
    void updatePosition() {
        gst_element_query_position(playbin, GST_FORMAT_TIME, &position);
        auto tempPosition = (double)position /duration;
        emit videoPlayer->watchPosition(tempPosition);
        if (tempPosition == duration) {
            timer.pause();
        }
    }
    static GstClockReturn sendSignal(GstClock*, GstClockTime, GstClockID id, PlayerObj* videoPlayer) {
        videoPlayer->updatePosition();
        return GST_CLOCK_OK;
    }
};

GstBusSyncReply handle_message(GstBus* bus, GstMessage* message, PlayerObj* playerObj)
{
    switch (GST_MESSAGE_TYPE(message)) {
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
        if (GST_MESSAGE_SRC(message) == GST_OBJECT(playerObj->playbin)) {
            if (new_state == GST_STATE_PLAYING) {
                playerObj->timer.start();
            }
            else if (new_state == GST_STATE_PAUSED) {
                playerObj->timer.pause();
            }
        }
        break;
    }
    case GST_MESSAGE_STREAM_START: {
        gst_element_query_duration(playerObj->playbin, GST_FORMAT_TIME, &playerObj->duration);
        break;
    }
    default:
        break;
    }
    gst_message_unref(message);
    return GST_BUS_DROP;
}


struct VideoPlayer::Obj:public PlayerObj{
    Obj(VideoPlayer * videoPlayer):PlayerObj(videoPlayer){}
};

VideoPlayer::VideoPlayer(QWidget * parent):
                QWidget(parent),
                _obj(new VideoPlayer::Obj(this)){
}

VideoPlayer::~VideoPlayer(){
    delete _obj;
}

bool VideoPlayer::openFile(const char * path){
    if(_obj->playbin){
        gst_element_set_state(_obj->playbin, GST_STATE_NULL);
        g_object_set(_obj->playbin, "uri",path, NULL);
        return true;
    }
    return false;
}

bool VideoPlayer::play(){
    if(_obj->playbin){
        GstStateChangeReturn state = gst_element_set_state(_obj->playbin,GST_STATE_PLAYING);
        bool status = state != GST_STATE_CHANGE_FAILURE;
        emit watchPlay(status);
        return status;
    }
    return false;
}

bool VideoPlayer::pause(){
    emit watchPlay(false);
    if(_obj->playbin){
         GstStateChangeReturn state = gst_element_set_state(_obj->playbin,GST_STATE_PAUSED);
         return state != GST_STATE_CHANGE_FAILURE;
    }
    return false;
}

void VideoPlayer::stop(){

}

bool VideoPlayer::addStepUp(long long step){
    if(_obj->playbin){
        auto tempPosition = _obj->position + step;
        _obj->position = tempPosition < _obj->duration ? tempPosition > 0 ? tempPosition: 0: _obj->duration;
        return gst_element_seek_simple(_obj->playbin, GST_FORMAT_TIME,
            (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH), _obj->position);
    }
    return false;
}

bool VideoPlayer::addStepDown(long long step){
    if(_obj->playbin){
        auto tempPosition = _obj->position - step;
        _obj->position = tempPosition < _obj->duration ? tempPosition > 0 ? tempPosition: 0: _obj->duration;
        return gst_element_seek_simple(_obj->playbin, GST_FORMAT_TIME,
            (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH), _obj->position);
    }
    return false;
}

void VideoPlayer::setMute(bool mute){
    if(_obj->playbin){
        g_object_set(G_OBJECT(_obj->playbin),"mute",mute, NULL);
    }
}

void VideoPlayer::setVolume(double volume){
    if(_obj->playbin){
        g_object_set(G_OBJECT(_obj->playbin), "volume",volume, NULL);
    }
}

long long VideoPlayer::getDuration(){
    return _obj->duration;
}

long long VideoPlayer::getPosition(){
    gst_element_query_position (_obj->playbin,GST_FORMAT_TIME,&_obj->position);
    return _obj->position;
}

void VideoPlayer::setPosition(long long position){
    if(_obj->playbin){
        gst_element_seek_simple(_obj->playbin, GST_FORMAT_TIME,
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


