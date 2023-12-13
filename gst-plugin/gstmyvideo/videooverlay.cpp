#include "gstmyvideo.h"
#include "videooverlay.h"

void expose(GstVideoOverlay *overlay){
    GstmyVideo * filter = GST_MYVIDEO(overlay);
    gst_video_overlay_expose(GST_VIDEO_OVERLAY(filter->videoSink));
}

void handle_events(GstVideoOverlay *overlay, gboolean handle_events){
    GstmyVideo * filter = GST_MYVIDEO(overlay);
    gst_video_overlay_handle_events(GST_VIDEO_OVERLAY(filter->videoSink),handle_events);
}

void set_render_rectangle(GstVideoOverlay *overlay,
                                 gint x, gint y,
                                 gint width, gint height){
    GstmyVideo * filter = GST_MYVIDEO(overlay);
    gst_video_overlay_set_render_rectangle(GST_VIDEO_OVERLAY(filter->videoSink),x,y,width,height);
}

void set_window_handle(GstVideoOverlay *overlay, guintptr handle)
{
    GstmyVideo * filter = GST_MYVIDEO(overlay);
    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY(filter->videoSink),handle);
}

void gst_my_video_videoOverlay_interface_init(GstVideoOverlayInterface *iface){
    iface->expose = expose;
    iface->handle_events = handle_events;
    iface->set_render_rectangle = set_render_rectangle;
    iface->set_window_handle = set_window_handle;
}
