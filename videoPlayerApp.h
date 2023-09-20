#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_videoPlayerApp.h"
#include <QtWidgets>

#include "glib.h"
#include "gst/gst.h"
#include "gst/video/videooverlay.h"
#include "gst/video/navigation.h"
#include "gst/video/colorbalance.h"

#include <QTimer>

class QtVideo : public QMainWindow
{
    Q_OBJECT
public:
    QtVideo(QWidget *parent = nullptr);
    ~QtVideo();
Q_SIGNALS:
    void signalFullScreen(bool status);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
private slots:
    void showFullScreen(bool checked);
    void on_openFille_triggered();
    void on_horizontalSliderVideoDuration_valueChanged(int value);

    void on_horizontalSliderSoundDuration_valueChanged(int value);

private:
    QWidget *menu;
    Ui::QtVideo ui;
    GstBus * bus;
    bool boolFullScreen;
    int maxStep;
    gint64 duration;
};
