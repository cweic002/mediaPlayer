#pragma once

#include "controller/position/position.h"
#include "model/videoPlayer/videoPlayer.h"

namespace Controller {
    namespace Position {
        struct VideoPlayer : public ControllerCRTP<Model::VideoPlayer>, public IPosition{
        public:
            VideoPlayer(Model::VideoPlayer * modelVideoPlayer);
            VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer);
            void setPosition(double volume) override;
            void setStep(std::chrono::milliseconds step) override;
            double getPosition() override;
        };
    }
}
