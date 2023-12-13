cmake_minimum_required(VERSION 3.5)

project(controllerOpenFileVideoPlayer)

# set(CMAKE_AUTOMOC OFF)

add_library(controllerOpenFileVideoPlayer
"videoPlayer.h"
"videoPlayer.cpp")

target_link_libraries(controllerOpenFileVideoPlayer PUBLIC modelVideoPlayer)