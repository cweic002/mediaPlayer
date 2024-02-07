#include "fGstDecodebin.h"

GstElement * Object::Factory::FGstDecodebin::createGstElement(){
    return gst_element_factory_make("decodebin","decodebin");
}
