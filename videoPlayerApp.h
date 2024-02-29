#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets>
#include <QTimer>
#include "ui_videoPlayerApp.h"
#include "Interface/iVideoPlayer/iVideoPlayer.h"
#include "interface/iBotomMenu/iBotomMenuPlayer/iBotomMenuPlayer.h"

class QtVideo : public QMainWindow
{
    Q_OBJECT
public:
    template<typename VideoPlayer,typename BotomMenuPlayer>
    QtVideo(QApplication * app,VideoPlayer * videoPlayer,BotomMenuPlayer botomMenuPlayer,QWidget *parent = nullptr);
    ~QtVideo();
    void changeEvent(QEvent* ре) override;
    void contextMenuEvent(QContextMenuEvent * pe) override;
Q_SIGNALS:
    void signalFullScreen(bool status);
    void fileNameChanged(QString & file);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private slots:
    void on_openFille_triggered();
private:
    QApplication * app_;
    Interface::IVideoPlayer * videoPlayer_;
    Interface::IBotomMenuPlayer * botomMenuPlayer_;
    QMenu* contextMenu_;
    Ui::QtVideo ui_;
    QTranslator translator_;
    bool boolFullScreen_;
};

#include "videoPlayerApp.inl"
