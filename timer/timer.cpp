#include "timer.h"

Timer::Timer(GstClock* clock, GstClockCallback sendSignal, gpointer user_data) :
    _clock(clock), 
    _clockID((void*)TimerFlags::TIMER_FLAG_PAUSE),
    _sendSignal(sendSignal),
    _user_data(user_data){
}

void Timer::start() {
    if (!_clockID) {
        GstClockTime start = gst_clock_get_internal_time(_clock);
        GstClockTime interval = GST_MSECOND * 50;
        _clockID = gst_clock_new_periodic_id(_clock, start, interval);
        gst_clock_id_wait_async(_clockID,_sendSignal,_user_data, NULL);
        gst_clock_id_unref(_clockID);
    }
}

void Timer::pause() {
    if (_clockID) {
        gst_clock_id_unschedule(_clockID);
        _clockID = (void*)TimerFlags::TIMER_FLAG_PAUSE;
    }
}

Timer::~Timer() {
    if (_clockID) {
        gst_clock_id_unschedule(_clockID);
        _clockID = (void*)TimerFlags::TIMER_FLAG_PAUSE;
    }
}