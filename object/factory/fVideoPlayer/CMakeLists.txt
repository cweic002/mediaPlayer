cmake_minimum_required(VERSION 3.5)

project(objectFVideoPlayer)
add_library(objectFVideoPlayer
    "fVideoPlayer.h"
    "fVideoPlayer.cpp")

target_link_libraries(objectFVideoPlayer PUBLIC objectVideoPlayer)
target_include_directories(objectFVideoPlayer PUBLIC ${videoPlayerApp_SOURCE_DIR})

target_link_libraries(objectFVideoPlayer PRIVATE objectFGstSrc)
target_link_libraries(objectFVideoPlayer PRIVATE objectFGstDecodebin)
target_link_libraries(objectFVideoPlayer PRIVATE objectFGstMyPlaginAudio)
target_link_libraries(objectFVideoPlayer PRIVATE objectFGstMyPlaginVideo)
