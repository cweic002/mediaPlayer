#include "playbinGstream.h"
#include "player/PlayerException.h"

template<typename FuncTimer>
PlaybinGstream::PlaybinGstream(FuncTimer funcTimer):
            playbin(gst_element_factory_make("playbin", "playbin")),
            duration(0),
            position(0),
            timer(gst_pipeline_get_clock((GstPipeline*)playbin),funcTimer),
            callBackPlay(nullptr),isPlay(false){
    auto bus = gst_element_get_bus(playbin);
    gst_bus_set_sync_handler(bus,(GstBusSyncHandler)handle_message,this, NULL);
    gst_object_unref(bus);
    if (!playbin) {
        throw PlayerException("Not all elements could be created");
    }
    int flags = 0;
    g_object_get(playbin, "flags", &flags, NULL);
    flags &= ~PlayFlags::PLAY_FLAG_TEXT;
    g_object_set(playbin, "flags", flags, NULL);
}

template <typename Func>
void PlaybinGstream::setCallBackPlay(Func func){
    auto fCallBack = [&](){
        func(isPlay);
    };
    callBackPlay = new CallBackFunc<decltype(fCallBack)>(fCallBack);
}
