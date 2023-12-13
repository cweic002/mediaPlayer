#include "videoPlayer.h"

inline void pad_video_handler(GstPad *new_pad, Model::VideoPlayer * modelVideoPlayer){
    GstPad *sink_pad = gst_element_get_static_pad(modelVideoPlayer->video,"video_sink");
    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    const gchar *new_pad_type = NULL;

    //g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

    /* If our converter is already linked, we have nothing to do here */
    if (gst_pad_is_linked(sink_pad)) {
      //g_print ("We are already linked. Ignoring.\n");
      goto exit;
    }

    /* Check the new pad's type */
    new_pad_caps = gst_pad_get_current_caps (new_pad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
    new_pad_type = gst_structure_get_name(new_pad_struct);
    if(!g_str_has_prefix(new_pad_type, "video/x-raw")){
      //g_print ("It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
      goto exit;
    }

    /* Attempt the link */
    ret = gst_pad_link (new_pad, sink_pad);
    if (GST_PAD_LINK_FAILED (ret)) {
      //g_print ("Type is '%s' but link failed.\n", new_pad_type);
    } else {
      g_print ("Link succeeded (type '%s').\n", new_pad_type);
    }

  exit:
    /* Unreference the new pad's caps, if we got them */
    if (new_pad_caps != NULL)
      gst_caps_unref (new_pad_caps);

    /* Unreference the sink pad */
    gst_object_unref (sink_pad);
}

inline void pad_audio_handler(GstPad *new_pad, Model::VideoPlayer * modelVideoPlayer){
    GstPad *sink_pad = gst_element_get_static_pad(modelVideoPlayer->audio,"sink");
    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    const gchar *new_pad_type = NULL;

    //g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

    /* If our converter is already linked, we have nothing to do here */
    if (gst_pad_is_linked (sink_pad)) {
      //g_print ("We are already linked. Ignoring.\n");
      goto exit;
    }

    /* Check the new pad's type */
    new_pad_caps = gst_pad_get_current_caps(new_pad);
    new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
    new_pad_type = gst_structure_get_name(new_pad_struct);
    if (!g_str_has_prefix (new_pad_type,"audio/x-raw")){
      //g_print ("It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
      goto exit;
    }

    /* Attempt the link */
    ret = gst_pad_link (new_pad, sink_pad);
    if (GST_PAD_LINK_FAILED (ret)) {
      //g_print ("Type is '%s' but link failed.\n", new_pad_type);
    } else {
      g_print ("Link succeeded (type '%s').\n", new_pad_type);
    }

  exit:
    /* Unreference the new pad's caps, if we got them */
    if (new_pad_caps != NULL)
      gst_caps_unref (new_pad_caps);

    /* Unreference the sink pad */
    gst_object_unref (sink_pad);
}

inline void pad_text_handler(GstPad *new_pad, Model::VideoPlayer * modelVideoPlayer){
    GstPad *sink_pad = gst_element_get_static_pad(modelVideoPlayer->video,"subtitle_sink");
    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    const gchar *new_pad_type = NULL;

    //g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

    /* If our converter is already linked, we have nothing to do here */
    if (gst_pad_is_linked (sink_pad)) {
      //g_print ("We are already linked. Ignoring.\n");
      goto exit;
    }

    /* Check the new pad's type */
    new_pad_caps = gst_pad_get_current_caps(new_pad);
    new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
    new_pad_type = gst_structure_get_name(new_pad_struct);
    // g_print ("Received new pad '%s' from '%s':\n",GST_PAD_NAME(new_pad), GST_ELEMENT_NAME (src));
    g_print ("It has type '%s'\n", new_pad_type);
    if (!g_str_has_prefix(new_pad_type,"text/x-raw")){
      g_print ("It has type '%s' which is not raw text. Ignoring.\n", new_pad_type);
      goto exit;
    }

    /* Attempt the link */
    ret = gst_pad_link(new_pad,sink_pad);
    if (GST_PAD_LINK_FAILED (ret)) {
      //g_print ("Type is '%s' but link failed.\n", new_pad_type);
    } else {
      g_print ("Link succeeded (type '%s').\n", new_pad_type);
    }

  exit:
    /* Unreference the new pad's caps, if we got them */
    if (new_pad_caps != NULL)
      gst_caps_unref (new_pad_caps);

    /* Unreference the sink pad */
    gst_object_unref (sink_pad);
}

inline void pad_added_handler(GstElement *, GstPad *new_pad, Model::VideoPlayer * modelVideoPlayer){
    pad_video_handler(new_pad,modelVideoPlayer);
    pad_text_handler(new_pad,modelVideoPlayer);
    pad_audio_handler(new_pad,modelVideoPlayer);
}

Controller::Init::VideoPlayer::VideoPlayer(Model::VideoPlayer * modelVideoPlayer):ControllerCRTP(modelVideoPlayer){}
Controller::Init::VideoPlayer::VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer):ControllerCRTP(modelVideoPlayer){}

//void ControllerInit<ModelVideoPlayer>::setModel(ModelVideoPlayer * modelVideoPlayer){
//    model=modelVideoPlayer;
//}

//ModelVideoPlayer * ControllerInit<ModelVideoPlayer>::getModel(){
//    return model;
//}

inline void Controller::Init::VideoPlayer::init(){
    if(model){
        model->videoPlayer = gst_pipeline_new("videoPlayer");
        model->src = gst_element_factory_make ("filesrc",NULL);
        model->decodebin = gst_element_factory_make("decodebin",NULL);
        model->video = gst_element_factory_make("myVideo","video");
        model->audio = gst_element_factory_make("audio","audio");

        gst_bin_add_many(GST_BIN(model->videoPlayer),model->src,
                         model->decodebin,model->video,model->audio,NULL);
        gst_element_link(model->src,model->decodebin);
        
        g_signal_connect((GstElement*)(model->decodebin),"pad-added",G_CALLBACK(pad_added_handler),model.get());

        //auto bus = gst_element_get_bus(modelVideoPlayer->playbin);
        //gst_bus_set_sync_handler(bus,(GstBusSyncHandler)handle_message,this, NULL);
        //gst_object_unref(bus);
        // g_object_set(model->src,"location","D:\\Zona Downloads\\Maleficent.mkv", NULL);
    }
}

Controller::Init::VideoPlayer::~VideoPlayer(){
  if(model){
      gst_element_set_state(model->videoPlayer, GST_STATE_NULL);
      gst_object_unref(model->videoPlayer);
  }
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







