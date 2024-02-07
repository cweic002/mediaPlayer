cmake_minimum_required(VERSION 3.5)

project(plugin)

add_subdirectory(gstreamer)

if(ANDROID)
    message("ANDROID_GSTREAMER")
else()
    message("NO_ANDROID_GSTREAMER")
endif()


