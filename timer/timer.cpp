#include "timer.h"

GstClockReturn Timer::sendSignal(GstClock *clock, GstClockTime time, GstClockID id, Timer * timer){
    (*timer->_callBackTimer)();
    return GST_CLOCK_OK;
}

void Timer::start(){
    if (!_clockID) {
        GstClockTime start = gst_clock_get_internal_time(_clock);
        GstClockTime interval = GST_MSECOND * 50;
        _clockID = gst_clock_new_periodic_id(_clock, start, interval);
        gst_clock_id_wait_async(_clockID,(GstClockCallback)sendSignal,this, NULL);
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
