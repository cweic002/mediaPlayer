#pragma once
#include "interface/iPlayer/iPlayer.h"
#include "interface/iAudio/iAudio.h"
#include "interface/iVideoOutput/iVideoOutput.h"

namespace Interface{
    struct IVideoPlayer : public Interface::IPlayer, public Interface::IAudio,public Interface::IVideoOutput{
        virtual ~IVideoPlayer() = default;
    };
}
