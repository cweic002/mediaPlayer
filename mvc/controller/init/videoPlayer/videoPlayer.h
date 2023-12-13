#pragma once

#include "model/videoPlayer/videoPlayer.h"
#include "controller/init/init.h"

namespace Controller {
    namespace Init{
        class VideoPlayer:public ControllerCRTP<Model::VideoPlayer>, public IInit{
        public:
            VideoPlayer(Model::VideoPlayer * modelVideoPlayer = nullptr);
            VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer);
            void init() override;
            ~VideoPlayer();
        };
    }
}

// template <>
// class ControllerInit<Model<VideoPlayer>>:public Controller<Model<VideoPlayer>>, public IControllerInit{
// public:
//     ControllerInit(Model<VideoPlayer> * modelVideoPlayer = nullptr);
//     void init() override;
// };









