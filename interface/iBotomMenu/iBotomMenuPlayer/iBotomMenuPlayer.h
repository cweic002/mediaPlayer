#pragma once
#include <QtWidgets>

namespace Interface {
    struct IBotomMenuPlayer : public QWidget{
        Q_OBJECT
    public:
        explicit IBotomMenuPlayer(QWidget *parent = nullptr):QWidget(parent){}
        virtual ~IBotomMenuPlayer() = default;
        virtual double getVolume() = 0;
    public slots:
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
        virtual void setPosition(long long int position) = 0;
        virtual void setDuration(long long int duration) = 0;
        virtual void setActivate(bool activate) = 0;
    signals:
        void playPauseChanged(bool play);
        void stopChanged();
        void positionChanged(long long int position);
        void volumeChanged(double volume);
        void mutedChanged(bool muted);
    };
}
