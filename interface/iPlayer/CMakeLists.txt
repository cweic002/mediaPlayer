cmake_minimum_required(VERSION 3.5)

project(iPlayer VERSION 0.1 LANGUAGES CXX)

add_library(iPlayer "iPlayer.h")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

target_link_libraries(iPlayer PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
