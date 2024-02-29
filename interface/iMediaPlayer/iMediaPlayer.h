#pragma once
#include <QString>

namespace Interface{
    /**
     * @brief Basic interface for creating a media player
    */
    struct IMediaPlayer {
        virtual ~IMediaPlayer() = default;
        /**
         * @brief Set pause
        */
        virtual void pause() = 0;
        /**
         * @brief Set play
        */
        virtual void play() = 0;
        /**
         * @brief Set stop
        */
        virtual void stop() = 0;
        /**
         * @brief Set path to media file
        */
        virtual void setMedia(const QString & path) = 0;
        /**
         * @brief Set current media player position
        */
        virtual void setPosition(long long int position) = 0;
        /**
         * @brief Get duration media player
        */
        virtual long long int getDuration() = 0;
        /**
         * @brief Get current media player position
        */
        virtual long long int getPosition() = 0;
    };
}
