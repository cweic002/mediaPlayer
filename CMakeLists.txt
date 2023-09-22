cmake_minimum_required(VERSION 3.5)

project(videoPlayer VERSION 0.1 LANGUAGES CXX)

find_package(PkgConfig)

macro(find_gstreamer_component prefix pkg lib)
  pkg_check_modules(PC_${prefix} REQUIRED ${pkg})
  find_library(${prefix}_LIBRARIES NAMES ${lib} HINTS ${PC_${prefix}_LIBRARY_DIRS} ${PC_${prefix}_LIBDIR})
  list(APPEND gstreamer_INCLUDE_DIRS ${PC_${prefix}_INCLUDE_DIRS})
  list(APPEND gstreamer_LIBRARIES ${${prefix}_LIBRARIES})
  mark_as_advanced(${prefix}_LIBRARIES gstreamer_LIBRARIES gstreamer_INCLUDE_DIRS)
endmacro()

find_gstreamer_component(gst      gstreamer-1.0       gstreamer-1.0)
find_gstreamer_component(gstbase  gstreamer-base-1.0  gstbase-1.0)
find_gstreamer_component(gstapp   gstreamer-app-1.0   gstapp-1.0)
find_gstreamer_component(gstvideo gstreamer-video-1.0 gstvideo-1.0)
find_gstreamer_component(gstvideo gstreamer-video-1.0 gstvideo-1.0)
find_gstreamer_component(glib glib-2.0 glib-2.0)
find_gstreamer_component(gstgobject gobject-2.0 gobject-2.0)

message(STATUS "inc: ${gstreamer_INCLUDE_DIRS}")
message(STATUS "lib: ${gstreamer_LIBRARIES}")


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES videoPlayer_ru_RU.ts)

set(PROJECT_SOURCES
        sliderPlayer.h
        player/player.h
        player/playerException.h
        timer/timer.h
        videoPlayer/videoPlayer.h
        videoPlayerApp.h

        main.cpp
        sliderPlayer.cpp
        player/player.cpp
        player/playerException.cpp
        timer/timer.cpp
        videoPlayer/videoPlayer.cpp
        videoPlayerApp.cpp

        videoPlayerApp.ui
        videoPlayerApp.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(videoPlayer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET videoPlayer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    message("Qt_version ${QT_VERSION_MAJOR}")
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(videoPlayer SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(videoPlayer
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

if(WIN32)
    message(STATUS "Building for Windows")
elseif(UNIX)
    message(STATUS "Building for Unix")
endif()


target_link_libraries(videoPlayer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

include_directories(
  ${gstreamer_INCLUDE_DIRS}
)

target_link_libraries(videoPlayer PRIVATE
   ${gstreamer_LIBRARIES}
)

set_target_properties(videoPlayer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(videoPlayer)
endif()
