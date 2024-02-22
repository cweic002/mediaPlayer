#include "videoPlayerApp.h"
#include <QCursor>
// #include "widget/botomMenu/botomMenuPlayer/botomMenuPlayer.h"
// #include "widget/contexMenu/contexMenu.h"

QtVideo::~QtVideo(){}

void QtVideo::changeEvent(QEvent* pe)
{
    if (pe->type() == QEvent::LanguageChange){
        _ui.retranslateUi(this);
    }
    QWidget::changeEvent(pe);
}

void QtVideo::contextMenuEvent(QContextMenuEvent * pe){
    _context_menu->exec(pe->globalPos());
}

//menu
void QtVideo::on_openFille_triggered(){
    // const QString baseName = "videoPlayerApp_en_US.qm";
    // if (translator.load(":/i18n/" + baseName)){
    //     qDebug() << baseName <<Qt::endl;
    //     app->installTranslator(&translator);
    // }
    QString path = QFileDialog::getOpenFileName(this, tr("OpenFile"), QDir::currentPath(), "*.mkv *.webm *.mp4");
    if(!path.isEmpty())
    {
        emit fileNameChanged(path);
        _videoPlayer->play();
        //set path
        // videoPlayer->setMedia(pat);
        // //play
        // videoPlayer->play();
        // //set volume
        // auto volume = botomMenuPlayer->getVolume();
        // videoPlayer->setVolume(volume);
    }
}

//mouseDoubleClickEvent
void QtVideo::mouseDoubleClickEvent(QMouseEvent *event)
{
    _boolFullScreen = !_boolFullScreen;
    if(_boolFullScreen){
       this->QMainWindow::showFullScreen();
    }else{
        this->QMainWindow::showNormal();
    }
    emit signalFullScreen(_boolFullScreen);
}
