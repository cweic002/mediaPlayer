cmake_minimum_required(VERSION 3.5)

project(iVideoOutput VERSION 0.1 LANGUAGES CXX)

add_library(iVideoOutput
    "iVideoOutput.h")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

target_link_libraries(iVideoOutput PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
