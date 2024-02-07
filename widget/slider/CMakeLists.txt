cmake_minimum_required(VERSION 3.5)

project(widgetSlider)

add_library(widgetSlider
"slider.h"
"slider.cpp")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

target_link_libraries(widgetSlider PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(widgetSlider PUBLIC ${videoPlayerApp_SOURCE_DIR})
