#pragma once

#include <QWidget>
#include "view/view.h"
#include "model/videoPlayer/videoPlayer.h"

namespace View{
    class VideoPlayer : public QWidget, public ViewCRTP<Model::VideoPlayer>
    {
        Q_OBJECT
    public:
        VideoPlayer(QWidget *parent = nullptr,Model::VideoPlayer * modelVideoPlayer = nullptr);
        void setWindowHandle();
    };
};