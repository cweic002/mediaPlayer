cmake_minimum_required(VERSION 3.5)

project(iFGstElementAudio)
add_library(iFGstElementVideo "iFGstElementVideo.h")

target_link_libraries(iFGstElementVideo PUBLIC iGstElement)
