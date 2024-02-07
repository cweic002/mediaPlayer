#include "fGstSrc.h"

GstElement * Object::Factory::FGstSrc::createGstElement(){
    return gst_element_factory_make ("filesrc","filesrc");
}
