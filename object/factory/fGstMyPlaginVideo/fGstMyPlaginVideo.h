#pragma once

#include "interface/iFactory/iFGstVideoOverlay/iFGstVideoOverlay.h"

namespace Object{
    namespace Factory{
class FGstMyPlaginVideo : public Interface::Factory::IFGstVideoOverlay{
        public:
            GstVideoOverlay * createGstVideoOverlay() override;
        };
    }
};
