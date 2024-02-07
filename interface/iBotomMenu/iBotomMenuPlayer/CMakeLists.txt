cmake_minimum_required(VERSION 3.5)

project(iBotomMenuPlayer)

add_library(iBotomMenuPlayer
    "iBotomMenuPlayer.h")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets REQUIRED)

target_link_libraries(iBotomMenuPlayer PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
