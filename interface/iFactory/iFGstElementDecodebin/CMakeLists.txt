cmake_minimum_required(VERSION 3.5)

project(iFGstElementDecodebin)
add_library(iFGstElementDecodebin "iFGstElementDecodebin.h")

target_link_libraries(iFGstElementDecodebin PUBLIC iGstElement)
