#include "timer.h"
#include<QDebug>

GstClockReturn Timer::sendSignal(GstClock *, GstClockTime,GstClockID id, Timer * timer){
    emit timer->timeout();
}

Timer::Timer(GstClock * clock):_clock(clock),_clockID((void*)TimerFlags::TIMER_FLAG_PAUSE){
}

void Timer::start(){
    if(!_clockID){
        GstClockTime start = gst_clock_get_internal_time(_clock);
        GstClockTime interval = GST_MSECOND*50;
        _clockID = gst_clock_new_periodic_id(_clock,start,interval);
        gst_clock_id_wait_async(_clockID,(GstClockCallback)Timer::sendSignal,this,NULL);
        gst_clock_id_unref(_clockID);
    }
//    if(!gst_clock_periodic_id_reinit(_clock,_clockID,start,interval)){
//        qDebug()<<"error:gst_clock_periodic_id_reinit"<<endl;
//    }
}

void Timer::pause(){
    if(_clockID){
        gst_clock_id_unschedule(_clockID);
        _clockID = (void*)TimerFlags::TIMER_FLAG_PAUSE;
    }
}

Timer::~Timer(){
    if(_clockID){
        gst_clock_id_unschedule(_clockID);
        _clockID = (void*)TimerFlags::TIMER_FLAG_PAUSE;
    }
}
