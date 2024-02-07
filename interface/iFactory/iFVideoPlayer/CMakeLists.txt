cmake_minimum_required(VERSION 3.5)

project(iFVideoPlayer)
add_library(iFVideoPlayer "iFVideoPlayer.h")

target_link_libraries(iFVideoPlayer PUBLIC iVideoPlayer)
