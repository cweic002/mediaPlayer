#pragma once
#include <QWidget>

namespace Interface{
    struct IVideoOutput {
        virtual ~IVideoOutput() = default;
        virtual void setVideoOutput(QWidget * output) = 0;
    };
}
