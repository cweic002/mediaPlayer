#pragma once

#include "model/model.h"
#include "controller/controller.h"
#include <QObject>

namespace Controller{
    namespace Player{
        enum State {
            START,
            END,
            PLAYING,
            PAUSED,
            STOP,
        };
        class IPlayer : public QObject{
        Q_OBJECT
        public:
            virtual void play(bool isPlay) = 0 ;
            virtual void stop() = 0 ;
            virtual void init() = 0 ;
            IPlayer(QObject *parent = nullptr);
            virtual ~IPlayer();
        signals:
            void sendState(State status);
        };
    }
}