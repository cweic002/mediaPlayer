#pragma once
#include "interface/iVideoPlayer/iVideoPlayer.h"
#include "gst/video/videooverlay.h"

#include <gst/gst.h>
#include <QTimer>

namespace Object {
    class VideoPlayer : public QObject,public Interface::IVideoPlayer{
        Q_OBJECT
        GstElement * videoPlayer;
        GstElement * src;
        GstElement * decodebin;
        GstElement * audio;
        GstVideoOverlay * video;
        GstBus * bus;
        QTimer timer;
        GstState state;
        static void pad_added_handler(GstElement *, GstPad *new_pad, Object::VideoPlayer * VideoPlayer);
        void handle_message(GstBus* bus, GstMessage* message);
    public:
        enum Error {
            NoError,
            ResourceError,
            FormatError,
            NetworkError,
            AccessDeniedError,
            ServiceMissingError
        };
        explicit VideoPlayer(GstElement * gstElementSrc,
                             GstElement * gstElementDecodebin,
                             GstVideoOverlay * gstElementVideo,
                             GstElement * gstElementAudio,
                             QWidget *parent = nullptr);
        ~VideoPlayer();
        void busUpdate();
        long long int getDuration() override;
        long long int getPosition() override;
        void setVideoOutput(QWidget *output) override;
    public slots:
        void pause() override;
        void play() override;
        void stop() override;
        void setMedia(const QString & path) override;
        void setPosition(long long int position) override;
        void setMuted(bool muted) override;
        void setVolume(double volume) override;
        double getVolume() override;
    signals:
        void mediaStatusChanged(MediaStatus state);
        void stateChanged(State state);
        void durationChanged(long long int duration);
        void positionChanged(long long int position);
    };
}
