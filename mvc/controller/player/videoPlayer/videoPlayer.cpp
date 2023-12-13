#include "videoPlayer.h"

GstBusSyncReply Controller::Player::VideoPlayer::handle_message(GstBus* bus, GstMessage* message, Controller::Player::VideoPlayer * ControllerVideoPlayer)
{
    switch(GST_MESSAGE_TYPE(message)){
      case GST_MESSAGE_STATE_CHANGED:{
        GstState old_state, new_state, pending_state;
        gst_message_parse_state_changed(message, &old_state, &new_state, &pending_state);
        if (new_state == GST_STATE_PLAYING){
          ControllerVideoPlayer->funCallBack(true);
        }
        else if(new_state == GST_STATE_PAUSED){
          ControllerVideoPlayer->funCallBack(false);
        }
        break;
      }
      case GST_MESSAGE_STREAM_START: {
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

Controller::Player::VideoPlayer::VideoPlayer(Model::VideoPlayer * modelVideoPlayer):
                  ControllerCRTP(modelVideoPlayer){}
Controller::Player::VideoPlayer::VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer):
                  ControllerCRTP(modelVideoPlayer){}

inline bool Controller::Player::VideoPlayer::play(){
  if(model->videoPlayer){
    GstStateChangeReturn state = gst_element_set_state(model->videoPlayer,GST_STATE_PLAYING);
    bool status = state != GST_STATE_CHANGE_FAILURE;
    return status;
  }
  return false;
}

inline void Controller::Player::VideoPlayer::stop(){
  if(model->videoPlayer){
    gst_element_set_state(model->videoPlayer,GST_STATE_READY);
  }
}

inline void Controller::Player::VideoPlayer::pause(){
  if(model->videoPlayer){
    gst_element_set_state(model->videoPlayer,GST_STATE_PAUSED);
  }
}

inline void Controller::Player::VideoPlayer::setCallBack(std::function<void(bool)> funCallback){
  this->funCallBack = funCallback;
  this->bus = gst_element_get_bus(model->videoPlayer);
  gst_bus_set_sync_handler(this->bus,(GstBusSyncHandler)handle_message,this, NULL);
}

Controller::Player::VideoPlayer::~VideoPlayer(){
  gst_element_set_state(model->videoPlayer, GST_STATE_READY);
  gst_bus_set_sync_handler(this->bus,nullptr,nullptr, NULL);
  gst_object_unref(bus);
}