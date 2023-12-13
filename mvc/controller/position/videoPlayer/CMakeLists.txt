cmake_minimum_required(VERSION 3.5)

project(controllerPositionVideoPlayer)

# set(CMAKE_AUTOMOC OFF)

add_library(controllerPositionVideoPlayer
"videoPlayer.h"
"videoPlayer.cpp")

target_link_libraries(controllerPositionVideoPlayer PUBLIC modelVideoPlayer)