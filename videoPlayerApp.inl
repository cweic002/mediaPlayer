#include "videoPlayerApp.h"
#include <QCursor>
#include "widget/contexMenu/contexMenu.h"

template<typename VideoPlayer,typename BotomMenuPlayer,typename ConnectFunc>
QtVideo::QtVideo(QApplication * app,VideoPlayer * videoPlayer,BotomMenuPlayer botomMenuPlayer,ConnectFunc connectFunc,QWidget *parent):QMainWindow(parent),
    app(app),
    videoPlayer(videoPlayer),
    botomMenuPlayer(botomMenuPlayer),
    context_menu(new Widget::ContexMenu(this)),
    boolFullScreen(false)
{
    ui.setupUi(this);
    botomMenuPlayer->setParent(ui.centralWidget);
    botomMenuPlayer->setObjectName("botomMenuPlayer");
    ui.gridLayout->addWidget(botomMenuPlayer, 1, 1, 1, 1, Qt::AlignBottom);
    QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(botomMenuPlayer->sizePolicy().hasHeightForWidth());
    botomMenuPlayer->setSizePolicy(sizePolicy);

    videoPlayer->setVideoOutput(ui.display);
    connectFunc(videoPlayer,botomMenuPlayer);
}
