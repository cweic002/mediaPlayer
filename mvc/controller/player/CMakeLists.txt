cmake_minimum_required(VERSION 3.5)

project(controllerPlayer)
add_library(controllerPlayer
"player.h"
"player.cpp")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core)

add_subdirectory(videoPlayer)

target_include_directories(controllerPlayer PUBLIC ${mvc_SOURCE_DIR})
target_link_libraries(controllerPlayer PUBLIC Qt${QT_VERSION_MAJOR}::Core)
