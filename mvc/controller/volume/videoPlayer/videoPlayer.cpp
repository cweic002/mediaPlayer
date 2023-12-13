#include "videoPlayer.h"

Controller::Volume::VideoPlayer::VideoPlayer(Model::VideoPlayer * modelVideoPlayer):
          ControllerCRTP(modelVideoPlayer){}

Controller::Volume::VideoPlayer::VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer):
          ControllerCRTP(modelVideoPlayer){}

inline void Controller::Volume::VideoPlayer::setVolume(double volume){
  if(this->model && model->videoPlayer){
    if(model->audio){
      g_object_set(G_OBJECT(model->audio),"volume",volume, NULL);
    }
  }
}

inline double Controller::Volume::VideoPlayer::getVolume(){
  if(this->model && model->audio){
    gdouble volume;
    g_object_get(G_OBJECT(model->audio),"volume",&volume, NULL);
    return volume;
  }
  return 0.0;
}

// // #include "gst/video/videooverlay.h"
// // #include "gst/player/player.h"

// VideoPlayer::VideoPlayer(QWidget * parent):QWidget(parent)
// {
//     VideoPlayer::setWindowHandle(this->winId());
// }

// //bool VideoPlayer::play(){
// //    auto res = VideoPlayer::play();
// //    //emit watchPlay(res);
// //    return res;
// //}

// //bool VideoPlayer::pause(){
// //    auto res = VideoPlayer::pause();
// //    //emit watchPlay(false);
// //    return res;
// //}

// //void VideoPlayer::setPlay(bool play){
// //    if(play){
// //        VideoPlayer::play();
// //    }else{
// //        VideoPlayer::pause();
// //    }
// //}

// //void VideoPlayer::setMute(bool mute){
// //    VideoPlayer::setMute(mute);
// //}

// GstBusSyncReply VideoPlayer::handle_message(GstBus* bus, GstMessage* message, VideoPlayer * playbinGstream)
// {
//     if(GST_MESSAGE_SRC(message) == GST_OBJECT(playbinGstream->playbin)){
//         g_print("Got %s message\n", GST_MESSAGE_TYPE_NAME (message));
//         switch(GST_MESSAGE_TYPE(message)){
//         case GST_MESSAGE_ERROR: {
//             GError* err;
//             gchar* debug;
//             gst_message_parse_error(message, &err, &debug);
//             g_print("Error: %s\n", err->message);
//             g_error_free(err);
//             g_free(debug);
//             break;
//         }
//         case GST_MESSAGE_WARNING:{
//             GError* err;
//             gchar* debug;
//             gst_message_parse_warning(message, &err, &debug);
//             g_print("Warning: %s\n", err->message);
//             g_error_free(err);
//             g_free(debug);
//             break;
//         }
//         case GST_MESSAGE_INFO:{
//             GError* err;
//             gchar* debug;
//             gst_message_parse_info(message, &err, &debug);
//             g_print("Info: %s\n", err->message);
//             g_error_free(err);
//             g_free(debug);
//             break;
//         }
//     //    case GST_MESSAGE_TAG:{
//     //        GstTagList *tag_list = nullptr;
//     //        gchar* a = nullptr;
//     //        gst_message_parse_tag(message,&tag_list);
//     //        a = gst_tag_list_to_string(tag_list);
//     //        g_print("Tag: %s\n", a);
//     //        g_free(a);
//     //        break;
//     //    }
//         case GST_MESSAGE_BUFFERING:{
//             gint percent;
//             gst_message_parse_buffering(message,&percent);
//             g_print("Buffering: %d\n", percent);
//             break;
//         }
//         case GST_MESSAGE_STATE_CHANGED:{
//                 GstState old_state, new_state, pending_state;
//                 gst_message_parse_state_changed(message, &old_state, &new_state, &pending_state);
//                 g_print ("Pipeline state changed from %s to %s:\n",
//                     gst_element_state_get_name(old_state), gst_element_state_get_name (new_state));
//                 if (new_state == GST_STATE_PLAYING){
//                     if(!playbinGstream->isPlay){
//                         playbinGstream->isPlay = true;
//                         if(playbinGstream->callBackPlay){
//                             (*playbinGstream->callBackPlay)();
//                         }
//                         playbinGstream->timer.start();
//                     }
//                 }
//                 else if (new_state == GST_STATE_PAUSED){
//                     if(playbinGstream->isPlay){
//                         playbinGstream->isPlay = false;
//                         if(playbinGstream->callBackPlay){
//                             (*playbinGstream->callBackPlay)();
//                         }
//                         playbinGstream->timer.pause();
//                     }
//                 }
//             break;
//         }
//         case GST_MESSAGE_STREAM_STATUS:{
//             GstStreamStatusType type;
//             GstElement *owner;
//             gst_message_parse_stream_status(message,&type,&owner);
//             g_print("STREAM_STATUS: %d\n", type);
//             break;
//         }
//         case GST_MESSAGE_STREAM_START: {
//             gst_element_query_duration(playbinGstream->playbin, GST_FORMAT_TIME, &playbinGstream->duration);
//             break;
//         }
//         default: {
//             break;
//         }
//         }
//     }
//     gst_message_unref(message);
//     return GST_BUS_DROP;
// }

// VideoPlayer::~VideoPlayer() {
//     gst_element_set_state(playbin, GST_STATE_NULL);
//     gst_object_unref(playbin);
// }

// void VideoPlayer::stop(){}

// bool VideoPlayer::openFile(const char * path){
//     if(playbin){
//         //gst_element_set_state(playbin, GST_STATE_NULL);
//         //g_object_set(playbin, "uri",path, NULL);

//         //g_object_set(filesink, "location","C:\\Users\\Cweic002\\Desktop\\2.mkv", NULL);

//         return true;
//     }
//     return false;
// }

// bool VideoPlayer::play(){
//     if(playbin){
//         GstStateChangeReturn state = gst_element_set_state(playbin,GST_STATE_PLAYING);
//         bool status = state != GST_STATE_CHANGE_FAILURE;
//         return status;
//     }
//     return false;
// }

// bool VideoPlayer::pause(){
//     if(playbin){
//          GstStateChangeReturn state = gst_element_set_state(playbin,GST_STATE_PAUSED);
//          return state != GST_STATE_CHANGE_FAILURE;
//     }
//     return false;
// }

// bool VideoPlayer::addStepUp(gint64 step){
//     if(playbin){
//         auto position = getPosition();
//         auto tempPosition = position + step;
//         position = tempPosition <duration ? tempPosition > 0 ? tempPosition: 0: duration;
//         return gst_element_seek_simple(playbin, GST_FORMAT_TIME,
//             (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH),position);
//     }
//     return false;
// }

// bool VideoPlayer::addStepDown(gint64 step){
//     if(playbin){
//         auto position = getPosition();
//         auto tempPosition = position - step;
//         position = tempPosition < duration ? tempPosition > 0 ? tempPosition: 0: duration;
//         return gst_element_seek_simple(playbin, GST_FORMAT_TIME,
//             (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH), position);
//     }
//     return false;
// }

// void VideoPlayer::setMute(bool mute){
//     if(playbin){
//         g_object_set(G_OBJECT(audio),"mute",mute, NULL);
//     }
// }

// void VideoPlayer::setVolume(double volume){
//     if(playbin){
//         g_object_set(G_OBJECT(audio),"volume",volume, NULL);
//     }
// }

// void VideoPlayer::setSubtitle(unsigned int index){
// //    GstPad *sink_pad = gst_element_get_static_pad(subtitleoverlay,"subtitle_sink");
// //    GstPad *old_src_pad = gst_pad_get_peer(sink_pad);
// //    gchar* str = (gchar*)(QString("src_")+QString::number(index)).toStdString().data();
// //    GstPad *src_pad = gst_element_get_static_pad(decodebin,str);
// //    if(old_src_pad != src_pad){
// //        GstPadLinkReturn ret;
// //        GstCaps *pad_caps = NULL;
// //        GstStructure *pad_struct = NULL;
// //        const gchar *pad_type = NULL;
// //        if(old_src_pad){
// //            gst_pad_unlink(old_src_pad,sink_pad);
// //        }
// //        if(src_pad){
// //            pad_caps = gst_pad_get_current_caps(src_pad);
// //            pad_struct = gst_caps_get_structure(pad_caps,0);
// //            pad_type = gst_structure_get_name(pad_struct);
// //            ret = gst_pad_link(src_pad,sink_pad);
// //            if (GST_PAD_LINK_FAILED(ret)){
// //              g_print ("Type is '%s' but link failed.\n", pad_type);
// //            } else {
// //              g_print ("Link succeeded (type '%s').\n", pad_type);
// //            }
// //            gst_caps_unref(pad_caps);
// //            pause();
// //            play();
// //        }
// //    }
// //    if(src_pad){
// //        gst_object_unref(src_pad);
// //    }
// //    if(old_src_pad){
// //        gst_object_unref(old_src_pad);
// //    }
// //    gst_object_unref(sink_pad);
// }

// gint64 inline VideoPlayer::getDuration(){
//     return duration;
// }

// gint64 inline VideoPlayer::getPosition(){
//     gint64 position;
//     gst_element_query_position(playbin,GST_FORMAT_TIME,&position);
//     return position;
// }

// void inline VideoPlayer::setPosition(gint64 position){
//     if(playbin){
//         gst_element_seek_simple(playbin, GST_FORMAT_TIME,
//             (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH),position);
//     }
// }

// void VideoPlayer::setWindowHandle(guintptr handle){
//     if(playbin){
//         gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(video),handle);
//     }
// }







