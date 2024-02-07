#include "fGstMyPlaginAudio.h"

GstElement * Object::Factory::FGstMyPlaginAudio::createGstElement(){
    return gst_element_factory_make("audio","audio");
}
