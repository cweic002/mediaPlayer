#ifndef PLAYBINGSTREAM_H
#define PLAYBINGSTREAM_H

#include "timer/Timer.h"
#include "player/player.h"

struct PlaybinGstream : public Player{
        enum PlayFlags {
            PLAY_FLAG_VIDEO = (1 << 0),
            PLAY_FLAG_AUDIO = (1 << 1),
            PLAY_FLAG_TEXT = (1 << 2)
        };
        GstElement* playbin;
        gint64 duration;
        gint64 position;
        Timer timer;
        ICallBackFunc * callBackPlay;
        bool isPlay;
        template<typename FuncTimer>
        PlaybinGstream(FuncTimer funcTimer);
        ~PlaybinGstream();
        void updatePosition();
        bool openFile(const char * path) override;
        bool play() override ;
        bool pause() override ;
        void stop() override ;
        bool addStepUp(long long step) override ;
        bool addStepDown(long long step) override ;
        void setMute(bool mute) override ;
        void setVolume(double volume) override ;
        long long getDuration() override ;
        long long getPosition() override ;
        void setPosition(long long position) override ;
        void setWindowHandle(guintptr handle);
        template <typename Func>
        void setCallBackPlay(Func func);
        private:
        static GstBusSyncReply handle_message(GstBus* bus, GstMessage* message, PlaybinGstream * playbinGstream);
    };
    
    #include "playbinGstream.inl"

#endif // PLAYBINGSTREAM_H
