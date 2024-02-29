#pragma once
#include "interface/iGstVideoPlayer/iGstVideoPlayer.h"
#include <QTimer>

namespace Object {
    class GstVideoPlayer : public QObject,public Interface::IGstVideoPlayer{
        Q_OBJECT
        GstElement * src_;
        GstElement * decodebin_;
        GstBus * bus_;
        QTimer timer_;
        GstState state_;
        static void pad_added_handler(GstElement *, GstPad *new_pad, Object::GstVideoPlayer * VideoPlayer);
        void handle_message(GstBus* bus, GstMessage* message);
    public:
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
        explicit GstVideoPlayer(QWidget *parent = nullptr);
        ~GstVideoPlayer();
        void busUpdate();
    public slots:
        void setMedia(const QString & path) override;
    signals:
        void mediaStatusChanged(MediaStatus state);
        void stateChanged(State state);
        void durationChanged(long long int duration);
        void positionChanged(long long int position);
    };
}
