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
    template<typename VideoPlayer,typename BotomMenuPlayer,typename ConnectFunc>
    QtVideo(QApplication * app,VideoPlayer * videoPlayer,BotomMenuPlayer botomMenuPlayer,ConnectFunc connectFunc,QWidget *parent = nullptr);
    ~QtVideo();
    void changeEvent(QEvent* ре) override;
    void contextMenuEvent(QContextMenuEvent * pe) override;
Q_SIGNALS:
    void signalFullScreen(bool status);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
private slots:
    void on_openFille_triggered();
private:
    QApplication * app;
    Interface::IVideoPlayer * videoPlayer;
    Interface::IBotomMenuPlayer * botomMenuPlayer;
    QMenu* context_menu;
    Ui::QtVideo ui;
    QTranslator translator;
    bool boolFullScreen;
};

#include "videoPlayerApp.inl"



