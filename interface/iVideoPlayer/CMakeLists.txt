cmake_minimum_required(VERSION 3.5)

project(iVideoPlayer VERSION 0.1 LANGUAGES CXX)

add_library(iVideoPlayer
    "iVideoPlayer.h")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

target_link_libraries(iVideoPlayer PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(iVideoPlayer PUBLIC iMediaPlayer)
target_link_libraries(iVideoPlayer PUBLIC iAudioPlayer)
target_link_libraries(iVideoPlayer PUBLIC iVideoOutput)
target_include_directories(iVideoPlayer PUBLIC ${videoPlayerApp_SOURCE_DIR})


