#pragma once

#include "controller/mute/mute.h"
#include "model/videoPlayer/videoPlayer.h"

namespace Controller {
    namespace Mute {
        struct VideoPlayer : public ControllerCRTP<Model::VideoPlayer>, public IMute{
        public:
            VideoPlayer(Model::VideoPlayer * modelVideoPlayer);
            VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer);
            void setMute(bool mute) override;
            bool getMute() override;
        };
    }
}
