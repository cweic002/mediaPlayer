#pragma once

#include "interface/iFactory/iFGstElementAudio/iFGstElementAudio.h"

namespace Object{
    namespace Factory{
        class FGstMyPlaginAudio : public Interface::Factory::IFGstElementAudio{
        public:
            GstElement * createGstElement() override;
        };
    }
};
