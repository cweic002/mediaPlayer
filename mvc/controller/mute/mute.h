#pragma once

#include "model/model.h"
#include "controller/controller.h"

namespace Controller {
    namespace Mute{
        struct IMute{
            virtual void setMute(bool mute) = 0;
            virtual bool getMute() = 0;
            virtual ~IMute(){}
        };
    }
}