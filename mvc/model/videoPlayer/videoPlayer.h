#pragma once

#include <gst/gst.h>
#include <model/model.h>

// struct VideoPlayer{
//     GstElement* videoPlayer;
//     GstElement *src;
//     GstElement *decodebin;
//     GstElement *video;
//     GstElement *audio;
//     //GstElement* filesink;
// };

namespace Model{
    struct VideoPlayer{
        GstElement * videoPlayer;
        GstElement * src;
        GstElement * decodebin;
        GstElement * video;
        GstElement * audio;
    };
}


