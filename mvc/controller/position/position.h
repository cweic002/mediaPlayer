#pragma once

#include "model/model.h"
#include "controller/controller.h"
#include <chrono>

namespace Controller {
    namespace Position{
        struct IPosition{
            virtual void setPosition(double position) = 0; 
            virtual double getPosition() = 0;
            virtual void setStep(std::chrono::milliseconds step) = 0;
            virtual ~IPosition(){}
        };
    }
}