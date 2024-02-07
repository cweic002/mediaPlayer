#pragma once

#include <gst/audio/streamvolume.h>
#include "gstaudio.h"

void gst_audio_streamVolume_interface_init(GstStreamVolumeInterface *iface);
void streamVolume_install_property(GObjectClass *gobject_class);
gboolean streamVolume_set_property(GstAudio *filter, guint prop_id,
                                   const GValue * value);
gboolean streamVolume_get_property(GstAudio *filter, guint prop_id,
                                    GValue * value);
