cmake_minimum_required(VERSION 3.5)

project(viewVideoPlayer)

add_library(viewVideoPlayer
"videoPlayer.h"
"videoPlayer.cpp")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

target_link_libraries(viewVideoPlayer PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(viewVideoPlayer PUBLIC ${mvc_SOURCE_DIR})
target_link_libraries(viewVideoPlayer PUBLIC modelVideoPlayer)

