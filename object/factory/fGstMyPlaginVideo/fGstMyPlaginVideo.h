#pragma once

#include "interface/iFactory/iFGstElementVideo/iFGstElementVideo.h"

namespace Object{
    namespace Factory{
        class FGstMyPlaginVideo : public Interface::Factory::IFGstElementVideo{
        public:
            GstElement * createGstElement() override;
        };
    }
};
