cmake_minimum_required(VERSION 3.5)

project(iGstAudioPlayer VERSION 0.1 LANGUAGES CXX)

add_library(iGstAudioPlayer
    "iGstAudioPlayer.h"
    "iGstAudioPlayer.cpp"
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

target_link_libraries(iGstAudioPlayer PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(iGstAudioPlayer PUBLIC ${videoPlayerApp_SOURCE_DIR})

target_link_libraries(iGstAudioPlayer PUBLIC iGstMediaPlayer)
