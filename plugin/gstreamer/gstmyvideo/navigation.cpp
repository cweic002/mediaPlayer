#include "navigation.h"
#include "gstmyvideo.h"

void gst_my_video_navigation_send_event(GstNavigation * navigation,GstStructure * structure){
    auto videoSink = GST_MYVIDEO(navigation)->videoSink;
    gst_navigation_send_event(GST_NAVIGATION(videoSink),structure);
}

void gst_my_video_navigation_send_event_simple(GstNavigation * navigation , GstEvent * event){
    auto videoSink = GST_MYVIDEO(navigation)->videoSink;
    gst_navigation_send_event_simple(GST_NAVIGATION(videoSink),event);
}

void gst_my_video_navigation_interface_init(GstNavigationInterface *iface){
    iface->send_event = gst_my_video_navigation_send_event;
    iface->send_event_simple = gst_my_video_navigation_send_event_simple;
}
