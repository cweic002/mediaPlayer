#pragma once

#include "controller/volume/volume.h"
#include "model/videoPlayer/videoPlayer.h"

namespace Controller {
    namespace Volume {
        struct VideoPlayer : public ControllerCRTP<Model::VideoPlayer>, public IVolume{
        public:
            VideoPlayer(Model::VideoPlayer * modelVideoPlayer);
            VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer);
            void setVolume(double volume) override;
            double getVolume() override;
        };
    }
}
