#include "streamvolume.h"
#include "enum_property.h"

void gst_audio_streamVolume_interface_init(GstStreamVolumeInterface *){}

void streamVolume_install_property(GObjectClass *gobject_class){
    g_object_class_install_property(gobject_class,PROP_VOLUME,
       g_param_spec_double("volume", "Volume", "Volume change",0.0,1.0,1.0,G_PARAM_READWRITE));
    g_object_class_install_property(gobject_class,PROP_MUTE,
        g_param_spec_boolean("mute", "Mute", "Mute change",false,G_PARAM_READWRITE));
}

gboolean streamVolume_set_property(GstAudio *filter, guint prop_id,
                               const GValue * value){
    switch(prop_id){
      case PROP_VOLUME:
        g_object_set(G_OBJECT(filter->volume),"volume",g_value_get_double(value),nullptr);
        return true;
      case PROP_MUTE:
        g_object_set(G_OBJECT(filter->volume),"mute",g_value_get_boolean(value),nullptr);
        return true;
    }
    return false;
}

gboolean streamVolume_get_property(GstAudio *filter, guint prop_id,
                                GValue * value){
    switch(prop_id){
      case PROP_VOLUME:
        gdouble volume;
        g_object_get(G_OBJECT(filter->volume),"volume",&volume,nullptr);
        g_value_set_double(value,volume);
        return true;
      case PROP_MUTE:
        gboolean mute;
        g_object_get(G_OBJECT(filter->volume),"mute",&mute,nullptr);
        g_value_set_double(value,volume);
        return true;
    }
    return false;
}
