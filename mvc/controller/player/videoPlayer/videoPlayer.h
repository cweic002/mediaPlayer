#pragma once

#include "controller/player/player.h"
#include "model/videoPlayer/videoPlayer.h"

namespace Controller{
    namespace Player{
        class VideoPlayer:public IPlayer, public ControllerCRTP<Model::VideoPlayer>{
            Q_OBJECT
            GstBus * bus;
            static GstBusSyncReply handle_message(GstBus* bus, GstMessage * message, Controller::Player::VideoPlayer * data);
        public:
            VideoPlayer(Model::VideoPlayer * modelVideoPlayer,QObject *parent = nullptr);
            VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer,QObject *parent = nullptr);
            void init() override;
            void play(bool isPlay) override;
            void stop() override;
            ~VideoPlayer();
        };
    }
};