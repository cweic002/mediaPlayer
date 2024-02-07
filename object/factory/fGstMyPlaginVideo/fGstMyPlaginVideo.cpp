#include "fGstMyPlaginVideo.h"

GstElement * Object::Factory::FGstMyPlaginVideo::createGstElement(){
    return gst_element_factory_make("myVideo","video");
}
