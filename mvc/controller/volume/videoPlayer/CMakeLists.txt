cmake_minimum_required(VERSION 3.5)

project(controllerVolumeVideoPlayer)

# set(CMAKE_AUTOMOC OFF)

add_library(controllerVolumeVideoPlayer
"videoPlayer.h"
"videoPlayer.cpp")

target_link_libraries(controllerVolumeVideoPlayer PUBLIC modelVideoPlayer)