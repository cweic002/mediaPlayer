#include "videoPlayerApp.h"
#include <QCursor>
#include "widget/contexMenu/contexMenu.h"

template<typename VideoPlayer,typename BotomMenuPlayer>
QtVideo::QtVideo(QApplication * app,VideoPlayer * videoPlayer,BotomMenuPlayer botomMenuPlayer,QWidget * parent):QMainWindow(parent),
    app_(app),
    videoPlayer_(videoPlayer),
    botomMenuPlayer_(botomMenuPlayer),
    contextMenu_(new Widget::ContexMenu(this)),
    boolFullScreen_(false)
{
    ui_.setupUi(this);
    botomMenuPlayer_->setParent(ui_.centralWidget);
    botomMenuPlayer_->setObjectName("botomMenuPlayer");
    ui_.gridLayout->addWidget(botomMenuPlayer, 1, 1, 1, 1, Qt::AlignBottom);
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(botomMenuPlayer->sizePolicy().hasHeightForWidth());
    botomMenuPlayer_->setSizePolicy(sizePolicy);
    videoPlayer_->setVideoOutput(ui_.display);
    connectVideoPlayerBotomMenuPlayer(videoPlayer,botomMenuPlayer);
    QObject::connect(this,&QtVideo::fileNameChanged,[videoPlayer = videoPlayer](QString & file){
        videoPlayer->setMedia(file);
    });
}
