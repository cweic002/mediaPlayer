cmake_minimum_required(VERSION 3.5)

project(iAudioPlayer VERSION 0.1 LANGUAGES CXX)

add_library(iAudioPlayer
    "iAudioPlayer.h")

target_include_directories(iAudioPlayer PUBLIC ${videoPlayerApp_SOURCE_DIR})
