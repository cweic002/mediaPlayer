#ifndef TIMER_H
#define TIMER_H

#include "gst/gst.h"
#include "callBackFunc/callBackFunc.h"

class Timer {
    GstClock* _clock;
    GstClockID _clockID;
    ICallBackFunc * _callBackTimer; 
    enum TimerFlags {
        TIMER_FLAG_PAUSE = 0
    };
    static GstClockReturn sendSignal(GstClock *clock, GstClockTime time, GstClockID id, Timer * timer);
public:
    template<typename Func>
    Timer(GstClock* clock, Func callBackFunc);
    void start();
    void pause();
    ~Timer();
};

#include "timer.inl"

#endif //TIMER_H