#include "videoPlayer.h"

inline void pad_added_handler(GstElement *, GstPad *new_pad, Model::VideoPlayer * modelVideoPlayer){
  GstPad *sink_pad_video = gst_element_get_static_pad(modelVideoPlayer->video,"video_sink");
  GstPad *sink_pad_subtitle = gst_element_get_static_pad(modelVideoPlayer->video,"subtitle_sink");
  GstPad *sink_pad_audio = gst_element_get_static_pad(modelVideoPlayer->audio,"sink");
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
      g_print ("Link succeeded (type '%s').\n", new_pad_type);
    }
  };

  /*link video */
  func(sink_pad_video,"video/x-raw");
  /*link subtitle */
  func(sink_pad_subtitle,"text/x-raw");
  /*link audio */
  func(sink_pad_audio,"audio/x-raw");

  gst_object_unref(sink_pad_video);
  gst_object_unref(sink_pad_subtitle);
  gst_object_unref(sink_pad_audio);

  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);
}

Controller::Init::VideoPlayer::VideoPlayer(Model::VideoPlayer * modelVideoPlayer):ControllerCRTP(modelVideoPlayer){}
Controller::Init::VideoPlayer::VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer):ControllerCRTP(modelVideoPlayer){}

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
    }
}

Controller::Init::VideoPlayer::~VideoPlayer(){
  if(model){
      gst_element_set_state(model->videoPlayer, GST_STATE_NULL);
      gst_object_unref(model->videoPlayer);
  }
}







