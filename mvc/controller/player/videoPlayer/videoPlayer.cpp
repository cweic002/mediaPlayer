#include "videoPlayer.h"

GstBusSyncReply Controller::Player::VideoPlayer::handle_message(GstBus* bus, GstMessage* message, Controller::Player::VideoPlayer * ControllerVideoPlayer)
{
    switch(GST_MESSAGE_TYPE(message)){
      case GST_MESSAGE_BUFFERING: {
        gint percent = 0;
        gst_message_parse_buffering (message, &percent);
        g_print ("Buffering (%u percent done)", percent);
        break;
      }
      case GST_MESSAGE_STATE_CHANGED:{
        g_print("GST_MESSAGE_STATE_CHANGED\n");
        GstState old_state, new_state, pending_state;
        gst_message_parse_state_changed(message, &old_state, &new_state, &pending_state);
        if (new_state == GST_STATE_PLAYING){
          emit ControllerVideoPlayer->sendState(State::PLAYING);
        }
        else if(new_state == GST_STATE_PAUSED){
          emit ControllerVideoPlayer->sendState(State::PAUSED);
        }
        else if(new_state == GST_STATE_READY){
          emit ControllerVideoPlayer->sendState(State::STOP);
        }
        break;
      }
      case GST_MESSAGE_PROGRESS:{
        g_print("GST_MESSAGE_PROGRESS\n");
      }
      case GST_MESSAGE_EOS:{
        g_print("GST_MESSAGE_EOS\n");
        emit ControllerVideoPlayer->sendState(State::END);
      }
      case GST_MESSAGE_STEP_DONE:{
        g_print("GST_MESSAGE_STEP_DONE\n");
      }
      case GST_MESSAGE_STREAM_START: {
        g_print("GST_MESSAGE_STREAM_START\n");
      // gst_element_query_duration(ControllerVideoPlayer->playbin, GST_FORMAT_TIME, &playbinGstream->duration);
        break;
      }
      default: {
        break;
      }
    }
  gst_message_unref(message);
  return GST_BUS_DROP;
}

void Controller::Player::VideoPlayer::init(){
  this->bus = gst_element_get_bus(model->videoPlayer);
  gst_bus_set_sync_handler(this->bus,(GstBusSyncHandler)handle_message,this, NULL);
}

Controller::Player::VideoPlayer::VideoPlayer(Model::VideoPlayer * modelVideoPlayer,QObject * parent):IPlayer(parent),
                  ControllerCRTP(modelVideoPlayer){
}
Controller::Player::VideoPlayer::VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer,QObject * parent):IPlayer(parent),
                  ControllerCRTP(modelVideoPlayer){
}

inline void Controller::Player::VideoPlayer::play(bool isPlay){
  if(model->videoPlayer){
    if(isPlay){
      gst_element_set_state(model->videoPlayer,GST_STATE_PLAYING);
    }else{
      gst_element_set_state(model->videoPlayer,GST_STATE_PAUSED);
    }
  }
}

inline void Controller::Player::VideoPlayer::stop(){
  if(model->videoPlayer){
    gst_element_set_state(model->videoPlayer,GST_STATE_READY);
  }
}

Controller::Player::VideoPlayer::~VideoPlayer(){
  gst_element_set_state(model->videoPlayer, GST_STATE_READY);
  gst_bus_set_sync_handler(this->bus,nullptr,nullptr, NULL);
  gst_object_unref(bus);
}