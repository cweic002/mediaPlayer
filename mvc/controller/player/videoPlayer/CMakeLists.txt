cmake_minimum_required(VERSION 3.5)

project(controllerPlayerVideoPlayer)

add_library(controllerPlayerVideoPlayer
"videoPlayer.h"
"videoPlayer.cpp")

target_link_libraries(controllerPlayerVideoPlayer PUBLIC modelVideoPlayer)
target_link_libraries(controllerPlayerVideoPlayer PUBLIC controllerPlayer)