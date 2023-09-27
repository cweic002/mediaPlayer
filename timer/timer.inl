#include "timer.h"

template<typename Func>
Timer::Timer(GstClock* clock,Func callBackFunc):
        _clock(clock), 
        _clockID((void*)TimerFlags::TIMER_FLAG_PAUSE),
        _callBackTimer(new CallBackFunc<Func>(callBackFunc)){

}