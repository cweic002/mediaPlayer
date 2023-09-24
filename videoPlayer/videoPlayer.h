#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include "player/player.h"

class VideoPlayer: public QWidget, public Player
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = nullptr);
    ~VideoPlayer();
    bool openFile(const char * path) override;
    bool play() override;
    bool pause() override;
    void stop() override;
    bool addStepUp(long long step) override;
    bool addStepDown(long long step) override;
    //bool setMuteOff() override;
    long long getDuration() override;
    long long getPosition() override;
    void setPosition(long long position) override;
public slots:
    void setMute(bool mute) override;
    void setVolume(double volume) override;
    void play(bool status);
Q_SIGNALS:
    void watchPosition(double share);
    void watchPlay(bool status);
private:
    struct Obj;
    Obj * _obj;
};

#endif // VIDEOPLAYER_H
