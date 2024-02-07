cmake_minimum_required(VERSION 3.5)

project(objectFGstSrc)
add_library(objectFGstSrc
    "fGstSrc.h"
    "fGstSrc.cpp")

target_link_libraries(objectFGstSrc PUBLIC iFGstElementSrc)
target_include_directories(objectFGstSrc PUBLIC ${videoPlayerApp_SOURCE_DIR})
