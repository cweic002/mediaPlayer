cmake_minimum_required(VERSION 3.5)

project(iFGstElementAudio)
add_library(iFGstElementAudio "iFGstElementAudio.h")

target_link_libraries(iFGstElementAudio PUBLIC iGstElement)
