#pragma once

#include "controller/player/player.h"
#include "model/videoPlayer/videoPlayer.h"

namespace Controller{
    namespace Player{
        class VideoPlayer: public ControllerCRTP<Model::VideoPlayer>,public IPlayer{
            std::function<void(bool)> funCallBack;
            GstBus * bus;
            static GstBusSyncReply handle_message(GstBus* bus, GstMessage * message, Controller::Player::VideoPlayer * data);
        public:
            VideoPlayer(Model::VideoPlayer * modelVideoPlayer);
            VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer);
            bool play() override;
            void stop() override;
            void pause() override;
            void setCallBack(std::function<void(bool)> funCallback) override;
            ~VideoPlayer();
        };
    }
};