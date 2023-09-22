#include "videoPlayerApp.h"
#include <iostream>
#include <QCursor>
#include <QCursor>

QtVideo::QtVideo(QWidget* parent):QMainWindow(parent),boolFullScreen(false)
{
    ui.setupUi(this);
    maxStep = ui.horizontalSliderVideoDuration->maximum();
    menu = new QWidget(this);
    auto hBoxLayoutMenu = new QHBoxLayout();
    auto buttonMenu = new QPushButton("asdasdasd");
    menu->setGeometry(0,0,50,100);
    hBoxLayoutMenu->addWidget(buttonMenu);
    menu->setLayout(hBoxLayoutMenu);
    menu->hide();
}

QtVideo::~QtVideo()
{}

//menu
void QtVideo::on_openFille_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Открыть файл"), QDir::currentPath(), tr("*.mkv *.webm *.mp4"));
    auto path2 = "file:///"+path;
    if(!path.isEmpty())
    {
        ui.widgetDisplay->openFile(path2.toUtf8().data());
        ui.widgetDisplay->play();
        //set volume
        gdouble val = (gdouble)ui.horizontalSliderSoundDuration->value()/ui.horizontalSliderSoundDuration->maximum();
        //ui.widgetDisplay->setVolume(val);
    }
}

//mouseDoubleClickEvent
void QtVideo::mouseDoubleClickEvent(QMouseEvent *event)
{
    boolFullScreen =!boolFullScreen;
    emit signalFullScreen(boolFullScreen);
}


void QtVideo::mousePressEvent(QMouseEvent *event){
    menu->move(event->x(),event->y());
    menu->show();
}


void QtVideo::showFullScreen(bool checked)
{
    if(checked){
        this->QMainWindow::showFullScreen();
    }else{
        this->QMainWindow::showNormal();
    }
}

void QtVideo::on_horizontalSliderVideoDuration_valueChanged(int value)
{
    gint64 position = (ui.widgetDisplay->getDuration()*value)/ui.horizontalSliderVideoDuration->maximum();
    ui.widgetDisplay->setPosition(position);
}


void QtVideo::on_horizontalSliderSoundDuration_valueChanged(int value)
{
        double volume = (gdouble)value/ui.horizontalSliderSoundDuration->maximum();
        ui.widgetDisplay->setVolume(volume);
}
