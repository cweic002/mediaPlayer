#ifndef TIMER_H
#define TIMER_H

#include "gst/gst.h"

class Timer {
    GstClock* _clock;
    GstClockID _clockID;
    GstClockCallback _sendSignal;
    gpointer _user_data;
    enum TimerFlags {
        TIMER_FLAG_PAUSE = 0
    };
public:
    Timer(GstClock* clock, GstClockCallback sendSignal, gpointer user_data);
    void start();
    void pause();
    ~Timer();
};

#endif //TIMER_H
