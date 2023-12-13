#pragma once

#include "model/model.h"
#include "controller/controller.h"
#include <functional>

namespace Controller{
    namespace Player{
        struct IPlayer{
            virtual bool play() = 0 ;
            virtual void stop() = 0 ;
            virtual void pause() = 0 ;
            virtual void setCallBack(std::function<void(bool)> funCallBack) = 0 ;
            virtual ~IPlayer(){};
        };
    }
}