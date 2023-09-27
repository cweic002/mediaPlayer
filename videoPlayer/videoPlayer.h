#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include "player/player.h"
#include "videoPlayer/playbinGstream.h"

class VideoPlayer: public QWidget, public PlaybinGstream
{
    Q_OBJECT
public:
    VideoPlayer(QWidget *parent = nullptr);
    bool play() override;
    bool pause() override;
public slots:
    void setMute(bool mute);
    void setPlay(bool play);
Q_SIGNALS:
    void watchPosition(double share);
    void watchPlay(bool status);
};

#endif // VIDEOPLAYER_H
