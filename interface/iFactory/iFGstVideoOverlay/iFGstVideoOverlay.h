#pragma once
#include "gst/video/videooverlay.h"

namespace Interface{
    namespace Factory{
        struct IFGstVideoOverlay{
            virtual GstVideoOverlay * createGstVideoOverlay() = 0;
        };
    }
};
