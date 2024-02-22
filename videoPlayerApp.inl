#include "videoPlayerApp.h"
#include <QCursor>
#include "widget/contexMenu/contexMenu.h"

template<typename VideoPlayer,typename BotomMenuPlayer,typename ConnectFunc>
QtVideo::QtVideo(QApplication * app,VideoPlayer * videoPlayer,BotomMenuPlayer botomMenuPlayer,ConnectFunc connectFunc,QWidget *parent):QMainWindow(parent),
    _app(app),
    _videoPlayer(videoPlayer),
    _botomMenuPlayer(botomMenuPlayer),
    _context_menu(new Widget::ContexMenu(this)),
    _boolFullScreen(false)
{
    _ui.setupUi(this);
    botomMenuPlayer->setParent(_ui.centralWidget);
    botomMenuPlayer->setObjectName("botomMenuPlayer");
    _ui.gridLayout->addWidget(botomMenuPlayer, 1, 1, 1, 1, Qt::AlignBottom);
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(botomMenuPlayer->sizePolicy().hasHeightForWidth());
    botomMenuPlayer->setSizePolicy(sizePolicy);
    videoPlayer->setVideoOutput(_ui.display);
    connectFunc(videoPlayer,botomMenuPlayer);

    QObject::connect(this,&QtVideo::fileNameChanged,videoPlayer,&VideoPlayer::setMedia);
}
