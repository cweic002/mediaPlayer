#include "videoPlayer.h"
#include "gst/video/videooverlay.h"
#include <QTimer>
#include <exception>

constexpr std::chrono::milliseconds updatetBusTimerInterval = std::chrono::milliseconds(100);

void Object::VideoPlayer::pad_added_handler(GstElement *, GstPad *new_pad, Object::VideoPlayer * videoPlayer){
    GstPad *sink_pad_video = gst_element_get_static_pad(GST_ELEMENT(videoPlayer->video),"video_sink");
    GstPad *sink_pad_subtitle = gst_element_get_static_pad(GST_ELEMENT(videoPlayer->video),"subtitle_sink");
    GstPad *sink_pad_audio = gst_element_get_static_pad(videoPlayer->audio,"sink");
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    const gchar *new_pad_type = NULL;

    new_pad_caps = gst_pad_get_current_caps (new_pad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
    new_pad_type = gst_structure_get_name(new_pad_struct);

    auto func = [new_pad,new_pad_type](GstPad * sink_pad,gchar * prefix){
        if(!gst_pad_is_linked(sink_pad) && g_str_has_prefix(new_pad_type, prefix)){
            GstPadLinkReturn ret = gst_pad_link(new_pad, sink_pad);
            if (!GST_PAD_LINK_FAILED (ret))
                // g_print ("Link succeeded (type '%s').\n", new_pad_type);
                qDebug()<<"Link succeeded (type'"<<new_pad_type<<"')."<<Qt::endl;
        }
    };

    /*link video */
    func(sink_pad_video,(gchar*)"video/x-raw");
    /*link subtitle */
    func(sink_pad_subtitle,(gchar*)"text/x-raw");
    /*link audio */
    func(sink_pad_audio,(gchar*)"audio/x-raw");

    gst_object_unref(sink_pad_video);
    gst_object_unref(sink_pad_subtitle);
    gst_object_unref(sink_pad_audio);

    if (new_pad_caps != NULL)
        gst_caps_unref (new_pad_caps);
}

void Object::VideoPlayer::handle_message(GstBus* bus, GstMessage* message){
    QString src_name = GST_MESSAGE_SRC_NAME(message);
    qDebug()<<"message SRC_NAME:"<<src_name;
    switch(GST_MESSAGE_TYPE(message)){
    case GST_MESSAGE_ERROR:{
        if (src_name == "filesrc"){
            emit mediaStatusChanged(MediaStatus::NoMedia);
        }else if(src_name == "typefind"){
            emit mediaStatusChanged(MediaStatus::InvalidMedia);
        }
        break;
    }
    case GST_MESSAGE_BUFFERING: {
        gint percent = 0;
        gst_message_parse_buffering(message, &percent);
        // g_print("Buffering (%u percent done)", percent);
        break;
    }
    case GST_MESSAGE_STATE_CHANGED:{
        if (src_name == "videoPlayer"){
            GstState old_state, new_state, pending_state;
            gst_message_parse_state_changed(message, &old_state, &new_state, &pending_state);
            switch(new_state){
            case GST_STATE_PLAYING:{
                qDebug()<<":"<<"GST_STATE_PLAYING";
                emit stateChanged(State::PlayingState);
                break;
            }
            case GST_STATE_PAUSED:{
                qDebug()<<":"<<"GST_STATE_PAUSED";
                emit stateChanged(State::PausedState);
                break;
            }
            case GST_STATE_READY:{
                qDebug()<<":"<<"GST_STATE_READY";
                emit stateChanged(State::StoppedState);
                break;
            }
            case GST_STATE_NULL:{
                qDebug()<<":"<<"GST_STATE_NULL";
                emit mediaStatusChanged(MediaStatus::NoMedia);
                break;
                }
            case GST_STATE_VOID_PENDING:{
                qDebug()<<":"<<"GST_STATE_VOID_PENDING";
                emit mediaStatusChanged(MediaStatus::UnknownMediaStatus);
                break;
            }
            }
            state=new_state;
        }
        break;
    }
    case GST_MESSAGE_EOS:{
        qDebug()<<":"<<"GST_MESSAGE_EOS";
        emit mediaStatusChanged(MediaStatus::EndOfMedia);
        break;
    }
    case GST_MESSAGE_STREAM_START: {
        qDebug()<<":"<<"GST_MESSAGE_STREAM_START";
        emit durationChanged(getDuration());
        emit mediaStatusChanged(MediaStatus::BufferingMedia);
        break;
    }
    default: {
        qDebug()<<":"<<"default";
        break;
    }
    }
    gst_message_unref(message);
}

Object::VideoPlayer::VideoPlayer(GstElement * gstElementSrc,
                                 GstElement * gstElementDecodebin,
                                 GstVideoOverlay * gstElementVideo,
                                 GstElement * gstElementAudio,
                                 QWidget *parent):QObject(parent),
                                                videoPlayer(gst_pipeline_new("videoPlayer")),
                                                src(gstElementSrc),
                                                decodebin(gstElementDecodebin),
                                                audio(gstElementAudio),
                                                video(gstElementVideo),
                                                state(GST_STATE_NULL){
    if(videoPlayer && src && decodebin && video && audio){
        gst_element_set_name(src,"filesrc");
        gst_bin_add_many(GST_BIN(videoPlayer),src,decodebin,GST_ELEMENT(video),audio,nullptr);
        gst_element_link(src,decodebin);

        this->bus = gst_element_get_bus(videoPlayer);
        g_signal_connect((GstElement*)(decodebin),"pad-added",G_CALLBACK(pad_added_handler),this);

        timer.setInterval(updatetBusTimerInterval);
        connect(&timer,&QTimer::timeout,this,&Object::VideoPlayer::busUpdate);
        timer.start();
    }else{
        gst_object_unref(this->videoPlayer);
        gst_object_unref(this->src);
        gst_object_unref(this->decodebin);
        gst_object_unref(this->video);
        gst_object_unref(this->audio);
        throw std::exception();
    }
}

Object::VideoPlayer::~VideoPlayer(){
    gst_element_set_state(this->videoPlayer, GST_STATE_NULL);
    timer.stop();
    gst_object_unref(bus);
    gst_object_unref(this->videoPlayer);
}

void Object::VideoPlayer::busUpdate(){
    GstMessage * message = gst_bus_pop(bus);
    while(message){
        handle_message(bus,message);
        message = gst_bus_pop(bus);
    }
    if(this->videoPlayer){
        if(GST_STATE_PLAYING==state){
            emit positionChanged(getPosition());
        }
    }
}

void Object::VideoPlayer::pause(){
    if(this->videoPlayer){
        gst_element_set_state(this->videoPlayer, GST_STATE_PAUSED);
    }
}

void Object::VideoPlayer::play(){
    if(this->videoPlayer){
        gst_element_set_state(this->videoPlayer, GST_STATE_PLAYING);
    }
}

void Object::VideoPlayer::stop(){
    if(this->videoPlayer){
        gst_element_set_state(this->videoPlayer, GST_STATE_READY);
    }
}

void Object::VideoPlayer::setMedia(const QString & path){
    if(this->videoPlayer && this->src){
        gst_element_set_state(this->videoPlayer, GST_STATE_NULL);
        g_object_set(this->src, "location",path.toUtf8().data(),nullptr);
    }
}

void Object::VideoPlayer::setVideoOutput(QWidget * output){
    gst_video_overlay_set_window_handle(this->video,output->winId());
}

gint64 Object::VideoPlayer::getDuration(){
    gint64 duration = 0;
    if(this->videoPlayer){
        gst_element_query_duration(this->videoPlayer, GST_FORMAT_TIME, &duration);
    }
    return duration;
}

void Object::VideoPlayer::setPosition(gint64 position){
    if(this->videoPlayer){
        gst_element_seek_simple(this->videoPlayer, GST_FORMAT_TIME,
            (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH),position);
    }
}

gint64 Object::VideoPlayer::getPosition(){
    gint64 position = 0;
    if(this->videoPlayer){
            gst_element_query_position(this->videoPlayer,GST_FORMAT_TIME,&position);
    }
    return position;
}

void Object::VideoPlayer::setMuted(bool muted){
    if(this->videoPlayer && this->audio){
        g_object_set(G_OBJECT(this->audio),"mute",muted, nullptr);
    }
}

void Object::VideoPlayer::setVolume(double volume){
    if(this->audio){
        g_object_set(G_OBJECT(this->audio),"volume",volume, nullptr);
    }
}

double Object::VideoPlayer::getVolume(){
    double volume = 0;
    if(this->audio){
        g_object_get(G_OBJECT(this->audio),"volume",&volume, nullptr);
    }
    return volume;
}
