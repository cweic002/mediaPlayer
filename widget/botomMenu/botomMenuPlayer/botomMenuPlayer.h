#pragma once
#include "interface/iBotomMenu/iBotomMenuPlayer/iBotomMenuPlayer.h"
#include <QStateMachine>

namespace Ui {
class BotomMenuPlayer;
}

namespace Widget {
    class BotomMenuPlayer : public Interface::IBotomMenuPlayer{
        Q_OBJECT
        long long int duration;
        void setPositionTimer(long long int position);
    public:
        explicit BotomMenuPlayer(QWidget *parent = nullptr);
        ~BotomMenuPlayer();
        double getVolume() override;
    public slots:
        void play() override;
        void pause() override;
        void stop() override;
        void setPosition(long long int position) override;
        void setDuration(long long int duration) override;
        void setActivate(bool activate) override;
    signals:
        void offActivate();
        void onActivate();
    private:
        Ui::BotomMenuPlayer *ui;
    };
}

