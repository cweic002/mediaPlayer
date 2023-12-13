#pragma once

#include "model/model.h"
#include "controller/controller.h"

namespace Controller {
    namespace Volume{
        struct IVolume{
            virtual void setVolume(double volume) = 0;
            virtual double getVolume() = 0;
            virtual ~IVolume(){}
        };
    }
}