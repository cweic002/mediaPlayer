#include "videoPlayer.h"
#include "ui_videoPlayer.h"

constexpr std::chrono::milliseconds updatetPositionTimerInterval = std::chrono::milliseconds(100);
constexpr std::chrono::milliseconds positionIntervalStep = std::chrono::milliseconds(15000);

Widget::VideoPlayer::VideoPlayer(Interface::IVideoPlayer * videoPlayer,QWidget * parent):QWidget(parent),
    _videoPlayer(videoPlayer),_timer(this),ui(new Ui::VideoPlayer){
    ui->setupUi(this);
    // timer.start( updatetPositionTimerInterval);
    videoPlayer->setVideoOutput(ui->Display);
    // connect(timer, &QTimer::timeout, this, &IVideoPlayer::positionChanged);
}

void Widget::VideoPlayer::setBotomMenuPlayer(Interface::IBotomMenuPlayer * botomMenuPlayer){
    ui->gridLayout->addWidget(botomMenuPlayer, 1, 1, 1, 1);
}

Widget::VideoPlayer::~VideoPlayer(){

}

// void Widget::VideoPlayer::pause(){
//     if(this->videoPlayer && this->src){
//         gchar * path = nullptr;
//         g_object_get(this->src,"location",&path,nullptr);
//         if(NULL != path){
//             // updateState(GST_STATE_PAUSED);
//             gst_element_set_state(this->videoPlayer, GST_STATE_PAUSED);
//         }
//     }
// }

// void Object::VideoPlayer::updateState(GstState newState){
//     GstState state;
//     GstState pending;
//     GstClockTime timeout = GST_TIME_AS_NSECONDS(1);
//     gst_element_get_state(this->videoPlayer,&state,&pending,timeout);
//     int i = 1;
//     if(newState<state){
//         i = -1;
//     }
//     while(state!=newState){
//         state = (GstState)((int)state+i);
//         gst_element_set_state(this->videoPlayer, state);
//         if(state == newState){
//             return;
//         }
//     }
// }

// void Widget::VideoPlayer::play(){
//     qDebug()<<"play"<<Qt::endl;
//     qDebug()<<this->videoPlayer<<Qt::endl;
//     qDebug()<<this->src<<Qt::endl;
//     if(this->videoPlayer && this->src){
//         qDebug()<<"play if"<<Qt::endl;
//         gchar * path = nullptr;
//         g_object_get(this->src,"location",&path,nullptr);
//         if(NULL != path){
//             gst_element_set_state(this->videoPlayer, GST_STATE_PLAYING);
//         }
//     }
// }

// void Widget::VideoPlayer::stop(){
//     if(this->videoPlayer && this->src){
//         gchar * path = nullptr;
//         g_object_get(this->src,"location",&path,nullptr);
//         if(NULL != path){
//             gst_element_set_state(this->videoPlayer, GST_STATE_READY);
//         }
//     }
// }

// void Widget::VideoPlayer::setMedia(const QString & path){
//     if(this->videoPlayer){
//         gst_element_set_state(this->videoPlayer, GST_STATE_NULL);
//         if(src){
//             g_object_set(this->src, "location",path.toUtf8().data(),nullptr);
//         }
//     }
// }

// void Widget::VideoPlayer::setMuted(bool muted){
//     if(this->videoPlayer){
//         if(this->audio){
//             g_object_set(G_OBJECT(this->audio),"mute",muted, nullptr);
//         }
//     }
// }

// gint64 Widget::VideoPlayer::getDuration(){
//     gint64 duration = 0;
//     if(this->audio){
//         gst_element_query_duration(this->videoPlayer, GST_FORMAT_TIME, &duration);
//     }
//     return duration;
// }

// void Widget::VideoPlayer::setPosition(gint64 position){
//     if(this->audio){
//         gst_element_seek_simple(this->videoPlayer, GST_FORMAT_TIME,
//             (GstSeekFlags)(GST_SEEK_FLAG_KEY_UNIT | GST_SEEK_FLAG_FLUSH),position);
//     }
// }

// gint64 Widget::VideoPlayer::getPosition(){
//     gint64 position = 0;
//     if(this->videoPlayer){
//         gst_element_query_position(this->videoPlayer,GST_FORMAT_TIME,&position);
//     }
//     return position;
// }

// void Widget::VideoPlayer::setVolume(double volume){
//     if(this->videoPlayer){
//         if(this->audio){
//             g_object_set(G_OBJECT(this->audio),"volume",volume, nullptr);
//         }
//     }
// }
