#include "fGstMyPlaginVideo.h"

GstVideoOverlay * Object::Factory::FGstMyPlaginVideo::createGstVideoOverlay(){
    return GST_VIDEO_OVERLAY(gst_element_factory_make("myVideo","video"));
}
