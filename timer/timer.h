#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QWidget>
#include "gst/gst.h"

class Timer : public QObject{
    Q_OBJECT
    GstClock * _clock;
    GstClockID _clockID;
    enum TimerFlags {
        TIMER_FLAG_PAUSE = 0
    };
    static GstClockReturn sendSignal(GstClock *clock, GstClockTime time,GstClockID id, Timer * timer);
public:
    Timer(GstClock * clock);
    void start();
    void pause();
    ~Timer();
public slots:

Q_SIGNALS:
    void timeout();
};


#endif //TIMER_H
