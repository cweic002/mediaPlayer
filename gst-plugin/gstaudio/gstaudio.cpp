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

#include "config.h"
#include "gstaudio.h"
#include "streamvolume.h"
#include "enum_property.h"

GST_DEBUG_CATEGORY_STATIC(gst_audio_debug);
#define GST_CAT_DEFAULT gst_audio_debug

//#define gst_audio_parent_class parent_class
//G_DEFINE_TYPE(GstAudio, gst_audio, GST_TYPE_BIN);

G_DEFINE_TYPE_WITH_CODE(GstAudio, gst_audio,GST_TYPE_BIN,
                        G_IMPLEMENT_INTERFACE(GST_TYPE_STREAM_VOLUME,gst_audio_streamVolume_interface_init));

GST_ELEMENT_REGISTER_DEFINE(audio,"audio",GST_RANK_NONE,GST_TYPE_AUDIO);

static void gst_audio_set_property(GObject * object,guint prop_id,const GValue * value,GParamSpec * pspec);
static void gst_audio_get_property(GObject * object,guint prop_id,GValue * value,GParamSpec * pspec);

/* initialize the gst_audio_class */
static void gst_audio_class_init(GstAudioClass * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  gobject_class->set_property = gst_audio_set_property;
  gobject_class->get_property = gst_audio_get_property;

  streamVolume_install_property(gobject_class);

  gst_element_class_set_details_simple(gstelement_class,
      "Audio",
      "FIXME:Generic",
      "FIXME:Generic Template Element", " <<user@hostname.org>>");
}

/* initialize the gst_audio */
static void gst_audio_init(GstAudio * filter)
{
  GstPad * sinkpad;

  filter->conv = gst_element_factory_make("audioconvert", NULL);
  filter->audioresample = gst_element_factory_make ("audioresample", NULL);
  filter->volume = gst_element_factory_make("volume",NULL);
  filter->audioSink = gst_element_factory_make("autoaudiosink",NULL);

  gst_bin_add_many(GST_BIN(filter),filter->conv,filter->audioresample,filter->volume,filter->audioSink,nullptr);
  gst_element_link_many(filter->conv,filter->audioresample,filter->volume,filter->audioSink,nullptr);

  sinkpad = gst_element_get_static_pad(filter->conv,"sink");
  gst_element_add_pad(GST_ELEMENT(filter),gst_ghost_pad_new("sink",sinkpad));
  gst_object_unref(sinkpad);
}

/* set property */
static void gst_audio_set_property(GObject * object, guint prop_id,
                                   const GValue * value, GParamSpec * pspec)
{
  GstAudio *filter = GST_AUDIO(object);

  gboolean result = !streamVolume_set_property(filter,prop_id,value);

  if(result){
      G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
  }
}

/* get property */
static void gst_audio_get_property(GObject * object, guint prop_id,
                                   GValue * value, GParamSpec * pspec)
{
    GstAudio *filter = GST_AUDIO (object);
    gboolean result = !streamVolume_get_property(filter,prop_id,value);

    if(result){
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    }
}

/* initialize the audio */
static gboolean audio_init(GstPlugin * audio)
{
  GST_DEBUG_CATEGORY_INIT(gst_audio_debug,"audio",0,"Template audio");
  return GST_ELEMENT_REGISTER(audio, audio);
}

GST_PLUGIN_DEFINE(GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    audio,
    "audio",
    audio_init,
    PACKAGE_VERSION, GST_LICENSE, GST_PACKAGE_NAME, GST_PACKAGE_ORIGIN)
