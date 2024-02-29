cmake_minimum_required(VERSION 3.5)

project(objectFGstVideoPlayer)
add_library(objectFGstVideoPlayer
    "fGstVideoPlayer.h"
    "fGstVideoPlayer.cpp")

target_link_libraries(objectFGstVideoPlayer PUBLIC objectGstVideoPlayer)
target_include_directories(objectFGstVideoPlayer PUBLIC ${videoPlayerApp_SOURCE_DIR})
