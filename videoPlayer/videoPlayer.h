#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QWidget>
#include <QTimer>

#include "glib.h"
#include "gst/gst.h"
#include "gst/video/videooverlay.h"
#include "gst/video/navigation.h"
#include "gst/video/colorbalance.h"
#include "player/playerException.h"

#include "player/player.h"
#include "timer/timer.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

class VideoPlayer: public QWidget, public Player
{
    Q_OBJECT
    GstElement * _playbin;
    gint64 _duration;
    gint64 _position;
    Timer timer;
    enum PlayFlags{
        PLAY_FLAG_VIDEO = (1 << 0),
        PLAY_FLAG_AUDIO = (1 << 1),
        PLAY_FLAG_TEXT  = (1 << 2)
    };
    static GstBusSyncReply handle_message(GstBus* bus, GstMessage* msg, VideoPlayer * videoPlayer);
    void includeWatch();
    void updatePosition();
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
};

#endif // VIDEOPLAYER_H
