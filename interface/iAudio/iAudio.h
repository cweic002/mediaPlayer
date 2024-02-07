#pragma once

namespace Interface{
    struct IAudio {
        virtual ~IAudio() = default;
        virtual void setMuted(bool muted) = 0;
        virtual void setVolume(double volume) = 0;
        virtual double getVolume() = 0;
    };
}
