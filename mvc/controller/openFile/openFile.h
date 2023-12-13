#pragma once

#include "model/model.h"
#include "controller/controller.h"

namespace Controller {
    namespace OpenFile {
        struct IOpenFile{
            void virtual open(char * src = nullptr) = 0;
            virtual ~IOpenFile(){}
        };
    }
}