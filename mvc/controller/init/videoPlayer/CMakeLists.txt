cmake_minimum_required(VERSION 3.5)

project(controllerInitVideoPlayer)

#set(CMAKE_AUTOMOC OFF)

add_library(controllerInitVideoPlayer
"videoPlayer.h"
"videoPlayer.cpp")

target_link_libraries(controllerInitVideoPlayer PUBLIC modelVideoPlayer)
