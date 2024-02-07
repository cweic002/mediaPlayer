cmake_minimum_required(VERSION 3.5)

project(widgetBotomMenuPlayer)

add_library(widgetBotomMenuPlayer
    "botomMenuPlayer.h"
    "botomMenuPlayer.cpp"
    "botomMenuPlayer.ui"
    "botomMenuPlayer.qrc")

target_link_libraries(widgetBotomMenuPlayer PUBLIC iBotomMenuPlayer)
target_link_libraries(widgetBotomMenuPlayer PUBLIC widgetSlider)

find_package(QT NAMES Qt6 Qt5)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS StateMachine)
target_link_libraries(widgetBotomMenuPlayer PUBLIC Qt${QT_VERSION_MAJOR}::StateMachine)


# find_package(Qt{QT_VERSION_MAJOR} REQUIRED COMPONENTS StateMachine)
# target_link_libraries(widgetBotomMenuPlayer PRIVATE Qt{QT_VERSION_MAJOR}::StateMachine)

target_include_directories(widgetBotomMenuPlayer PUBLIC ${videoPlayerApp_SOURCE_DIR})
