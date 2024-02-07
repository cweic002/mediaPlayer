#pragma once

#include "interface/iFactory/iFGstElementDecodebin/iFGstElementDecodebin.h"

namespace Object{
    namespace Factory{
        class FGstDecodebin : public Interface::Factory::IFGstElementDecodebin{
        public:
            GstElement * createGstElement() override;
        };
    }
};
