cmake_minimum_required(VERSION 3.5)

project(widgetVideoPlayer)

add_library(widgetVideoPlayer
"videoPlayer.h"
"videoPlayer.cpp"
"videoPlayer.ui")

target_link_libraries(widgetVideoPlayer PUBLIC iVideoPlayer)
target_include_directories(widgetVideoPlayer PUBLIC ${videoPlayerApp_SOURCE_DIR})
