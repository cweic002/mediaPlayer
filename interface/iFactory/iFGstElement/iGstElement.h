#pragma once
#include <gst/gst.h>

namespace Interface{
    namespace Factory{
        struct IFGstElement{
            virtual GstElement * createGstElement() = 0;
        };
    }
};
