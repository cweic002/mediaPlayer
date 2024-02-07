#pragma once

#include "interface/iFactory/iFGstElementSrc/iFGstElementSrc.h"

namespace Object{
    namespace Factory{
        class FGstSrc : public Interface::Factory::IFGstElementSrc{
        public:
            GstElement * createGstElement() override;
        };
    }
};
