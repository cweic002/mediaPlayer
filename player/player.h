#ifndef PLAYER_H
#define PLAYER_H

struct Player
{
    virtual ~Player();
    virtual bool openFile(const char * path) = 0;
    virtual bool play() = 0;
    virtual bool pause() = 0;
    virtual void stop() = 0;
    virtual bool addStepUp(long long step) = 0;
    virtual bool addStepDown(long long step) = 0;
    virtual void setMute(bool mute) = 0;
    virtual void setVolume(double volume) = 0;
    virtual long long getDuration() = 0;
    virtual long long getPosition() = 0;
    virtual void setPosition(long long position) = 0;
};

#endif // PLAYER_H
