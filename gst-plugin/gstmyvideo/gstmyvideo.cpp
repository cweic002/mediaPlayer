/*
 * GStreamer
 * Copyright (C) 2005 Thomas Vander Stichele <thomas@apestaart.org>
 * Copyright (C) 2005 Ronald S. Bultje <rbultje@ronald.bitfreak.net>
 * Copyright (C) 2023  <<user@hostname.org>>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Alternatively, the contents of this file may be used under the
 * GNU Lesser General Public License Version 2.1 (the "LGPL"), in
 * which case the following provisions apply instead of the ones
 * mentioned above:
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <config.h>

#include "gstmyvideo.h"
#include "navigation.h"
#include "videooverlay.h"

GST_DEBUG_CATEGORY_STATIC (gst_my_video_debug);
#define GST_CAT_DEFAULT gst_my_video_debug

enum
{
  PROP_0,
};

//#define gst_my_video_parent_class parent_class
//G_DEFINE_TYPE (GstmyVideo, gst_my_video, GST_TYPE_BIN);

G_DEFINE_TYPE_WITH_CODE(GstmyVideo, gst_my_video,GST_TYPE_BIN,
                        G_IMPLEMENT_INTERFACE(GST_TYPE_VIDEO_OVERLAY,gst_my_video_videoOverlay_interface_init);
                        G_IMPLEMENT_INTERFACE(GST_TYPE_NAVIGATION,gst_my_video_navigation_interface_init));
GST_ELEMENT_REGISTER_DEFINE(my_video, "myVideo", GST_RANK_NONE,GST_TYPE_MYVIDEO);

//static void gst_my_video_set_property (GObject * object,
//    guint prop_id, const GValue * value, GParamSpec * pspec);
//static void gst_my_video_get_property (GObject * object,
//    guint prop_id, GValue * value, GParamSpec * pspec);

static void gst_my_video_class_init(GstmyVideoClass * klass)
{
    GObjectClass *gobject_class;
    GstElementClass *gstelement_class;

    gobject_class = (GObjectClass *) klass;
    gstelement_class = (GstElementClass *) klass;

//    gobject_class->set_property = gst_my_video_set_property;
//    gobject_class->get_property = gst_my_video_get_property;

    gst_element_class_set_details_simple (gstelement_class,
        "myVideo",
        "FIXME:Generic",
        "FIXME:Generic Template Element", " <<user@hostname.org>>");
}

static void gst_my_video_init(GstmyVideo * filter)
{
    filter->subtitleoverlay = gst_element_factory_make ("subtitleoverlay", NULL);
    filter->videoSink = gst_element_factory_make("d3d11videosink", NULL);

    gst_bin_add_many(GST_BIN(filter),filter->subtitleoverlay,filter->videoSink,nullptr);
    gst_element_link_many(filter->subtitleoverlay,filter->videoSink,nullptr);

    GstPad * subtitle_sinkpad = gst_element_get_static_pad(filter->subtitleoverlay,"subtitle_sink");
    gst_element_add_pad(GST_ELEMENT(filter),gst_ghost_pad_new("subtitle_sink",subtitle_sinkpad));
    gst_object_unref(subtitle_sinkpad);

    GstPad * videoPad = gst_element_get_static_pad (filter->subtitleoverlay,"video_sink");
    gst_element_add_pad(GST_ELEMENT(filter),gst_ghost_pad_new("video_sink",videoPad));
    gst_object_unref(videoPad);
}

//static void
//gst_my_video_set_property (GObject * object, guint prop_id,const GValue * value, GParamSpec * pspec)
//{
//    GstmyVideo *filter = GST_MYVIDEO (object);
//    switch (prop_id){
//        default:
//            G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
//            break;
//    }
//}

//static void
//gst_my_video_get_property (GObject * object, guint prop_id,GValue * value, GParamSpec * pspec)
//{
//    GstmyVideo *filter = GST_MYVIDEO (object);
//    switch (prop_id) {
//        default:
//            G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
//            break;
//    }
//}


/* entry point to initialize the plug-in
 * initialize the plug-in itself
 * register the element factories and other features
 */
static gboolean
myvideo_init (GstPlugin * myvideo)
{
    GST_DEBUG_CATEGORY_INIT (gst_my_video_debug, "myvideo",
        0, "Template myvideo");
    return GST_ELEMENT_REGISTER (my_video, myvideo);
}

/* PACKAGE: this is usually set by meson depending on some _INIT macro
 * in meson.build and then written into and defined in config.h, but we can
 * just set it ourselves here in case someone doesn't use meson to
 * compile this code. GST_PLUGIN_DEFINE needs PACKAGE to be defined.
 */
#ifndef PACKAGE
#define PACKAGE "myfirstmyvideo"
#endif

/* gstreamer looks for this structure to register myvideos
 *
 * exchange the string 'Template myvideo' with your myvideo description
 */
GST_PLUGIN_DEFINE(GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    myvideo,
    "myVideo",
    myvideo_init,
    PACKAGE_VERSION, GST_LICENSE, GST_PACKAGE_NAME, GST_PACKAGE_ORIGIN)
