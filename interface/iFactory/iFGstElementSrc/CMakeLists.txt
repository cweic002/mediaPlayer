cmake_minimum_required(VERSION 3.5)

project(iFGstElementSrc)
add_library(iFGstElementSrc "iFGstElementSrc.h")

target_link_libraries(iFGstElementSrc PUBLIC iGstElement)
