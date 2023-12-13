#pragma once 

#include "controller/controller.h"

namespace Controller {
    namespace Init{
        struct IInit{
            void virtual init() = 0;
            virtual ~IInit(){}
        };
    }
}