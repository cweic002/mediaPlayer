#pragma once

#include "controller/openFile/openFile.h"
#include "model/videoPlayer/videoPlayer.h"

namespace Controller {
    namespace OpenFile {
        struct VideoPlayer : public ControllerCRTP<Model::VideoPlayer>, public IOpenFile{
            char * src;
        public:
            VideoPlayer(Model::VideoPlayer * modelVideoPlayer,char * src = nullptr);
            VideoPlayer(std::shared_ptr<Model::VideoPlayer> & modelVideoPlayer,char * src = nullptr);
            void open(char * src = nullptr) override;
        };
    }
}
