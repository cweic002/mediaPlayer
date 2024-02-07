cmake_minimum_required(VERSION 3.5)

project(widgetContexMenu)

add_library(widgetContexMenu
    "contexMenu.h"
    "contexMenu.cpp"
    "contexMenu.ui"
    "contexMenu.qrc")


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
target_link_libraries(widgetContexMenu PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(widgetContexMenu PUBLIC ${videoPlayerApp_SOURCE_DIR})
