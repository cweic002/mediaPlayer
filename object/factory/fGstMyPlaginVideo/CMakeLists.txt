cmake_minimum_required(VERSION 3.5)

project(objectFGstMyPlaginVideo)
add_library(objectFGstMyPlaginVideo
    "fGstMyPlaginVideo.h"
    "fGstMyPlaginVideo.cpp")

target_link_libraries(objectFGstMyPlaginVideo PUBLIC iFGstElementVideo)
target_include_directories(objectFGstMyPlaginVideo PUBLIC ${videoPlayerApp_SOURCE_DIR})
