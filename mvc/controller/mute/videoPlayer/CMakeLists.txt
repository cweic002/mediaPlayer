cmake_minimum_required(VERSION 3.5)

project(controllerMuteVideoPlayer)

# set(CMAKE_AUTOMOC OFF)

add_library(controllerMuteVideoPlayer
"videoPlayer.h"
"videoPlayer.cpp")

target_link_libraries(controllerMuteVideoPlayer PUBLIC modelVideoPlayer)