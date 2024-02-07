#pragma once
#include <QString>

namespace Interface{
    struct IPlayer {
        virtual ~IPlayer() = default;
        enum MediaStatus {
            UnknownMediaStatus,
            NoMedia,
            LoadingMedia,
            LoadedMedia,
            StalledMedia,
            BufferingMedia,
            BufferedMedia,
            EndOfMedia,
            InvalidMedia,
        };
        enum State{
            PlayingState,
            PausedState,
            StoppedState
        };
        virtual void pause() = 0;
        virtual void play() = 0;
        virtual void stop() = 0;
        virtual void setMedia(const QString & path) = 0;
        virtual void setPosition(long long int position) = 0;
        virtual long long int getDuration() = 0;
        virtual long long int getPosition() = 0;
    };
}
