cmake_minimum_required(VERSION 3.5)

project(objectFGstMyPlaginAudio)
add_library(objectFGstMyPlaginAudio
    "fGstMyPlaginAudio.h"
    "fGstMyPlaginAudio.cpp")

target_link_libraries(objectFGstMyPlaginAudio PUBLIC iFGstElementAudio)
target_include_directories(objectFGstMyPlaginAudio PUBLIC ${videoPlayerApp_SOURCE_DIR})
