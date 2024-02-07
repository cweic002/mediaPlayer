cmake_minimum_required(VERSION 3.5)

project(objectFGstDecodebin)
add_library(objectFGstDecodebin
    "fGstDecodebin.h"
    "fGstDecodebin.cpp")

target_link_libraries(objectFGstDecodebin PUBLIC iFGstElementDecodebin)
target_include_directories(objectFGstDecodebin PUBLIC ${videoPlayerApp_SOURCE_DIR})
