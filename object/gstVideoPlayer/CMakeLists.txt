cmake_minimum_required(VERSION 3.5)

project(objectGstVideoPlayer)

add_library(objectGstVideoPlayer
    "gstVideoPlayer.h"
    "gstVideoPlayer.cpp"
)

target_link_libraries(objectGstVideoPlayer PUBLIC iGstVideoPlayer)
