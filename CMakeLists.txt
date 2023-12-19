cmake_minimum_required(VERSION 3.5)

project(videoPlayerApp VERSION 0.1 LANGUAGES CXX)

find_package(PkgConfig)

macro(find_gstreamer_component prefix pkg lib)
  pkg_check_modules(PC_${prefix} REQUIRED ${pkg})
  find_library(${prefix}_LIBRARIES NAMES ${lib} HINTS ${PC_${prefix}_LIBRARY_DIRS} ${PC_${prefix}_LIBDIR})
  list(APPEND gstreamer_INCLUDE_DIRS ${PC_${prefix}_INCLUDE_DIRS})
  list(APPEND gstreamer_LIBRARIES ${${prefix}_LIBRARIES})
  mark_as_advanced(${prefix}_LIBRARIES gstreamer_LIBRARIES gstreamer_INCLUDE_DIRS)
endmacro()

find_gstreamer_component(gst      gstreamer-1.0       gstreamer-1.0)
find_gstreamer_component(glib glib-2.0 glib-2.0)
find_gstreamer_component(gstgobject gobject-2.0 gobject-2.0)
find_gstreamer_component(gthread gstreamer-1.0 gthread-2.0)


#find_gstreamer_component(gstbase  gstreamer-base-1.0  gstbase-1.0)
#find_gstreamer_component(gstapp   gstreamer-app-1.0   gstapp-1.0)
#find_gstreamer_component(gstvideo gstreamer-video-1.0 gstvideo-1.0)
#find_gstreamer_component(glib glib-2.0 glib-2.0)
#find_gstreamer_component(gstgobject gobject-2.0 gobject-2.0)
#find_gstreamer_component(gthread gstreamer-1.0 gthread-2.0)
#find_gstreamer_component(gstaudio gstreamer-audio-1.0 gstaudio-1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

find_package(QT NAMES Qt6 Qt5)

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

if(WIN32)
    message(STATUS "Building for Windows")
elseif(UNIX)
    message(STATUS "Building for Unix")
endif()

#set(TS_FILES videoPlayer_ru_RU.ts)
# qt5_add_resources(videoPlayerResourse videoPlayerApp.qrc)

# add_subdirectory(timer)
# add_subdirectory(player)
add_subdirectory(mvc)
#add_subdirectory(videoPlayer)
add_subdirectory(gst-plugin)

#target_include_directories(Tutorial PUBLIC
#                          "${PROJECT_BINARY_DIR}"
#                          "${PROJECT_SOURCE_DIR}/MathFunctions"
#                          )

include_directories(${gstreamer_INCLUDE_DIRS})

set(PROJECT_SOURCES
    # player/player.h
    # player/player.cpp
    # player/playerException.h
    # player/playerException.cpp
    # timer/timer.h
    # timer/timer.cpp
    # timer/timer.inl
    # videoPlayer/playbinGstream.h
    # videoPlayer/playbinGstream.cpp
    # videoPlayer/playbinGstream.inl
    # videoPlayer/videoPlayer.h
    # videoPlayer/videoPlayer.cpp
    sliderPlayer.h
    sliderPlayer.cpp
    main.cpp
    videoPlayerApp.h
    videoPlayerApp.cpp
    videoPlayerApp.ui
    videoPlayerApp.qrc
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(videoPlayerApp
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    message("Qt_version ${QT_VERSION_MAJOR}")
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(videoPlayerApp ${PROJECT_SOURCES})
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(videoPlayerApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(videoPlayerApp PRIVATE ${gstreamer_LIBRARIES})

set_target_properties(videoPlayerApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(videoPlayer)
endif()

target_link_libraries(videoPlayerApp PUBLIC controllerInitVideoPlayer)
target_link_libraries(videoPlayerApp PUBLIC controllerVolumeVideoPlayer)
target_link_libraries(videoPlayerApp PUBLIC controllerMuteVideoPlayer)
target_link_libraries(videoPlayerApp PUBLIC controllerOpenFileVideoPlayer)
target_link_libraries(videoPlayerApp PUBLIC controllerPlayerVideoPlayer)
target_link_libraries(videoPlayerApp PUBLIC controllerPositionVideoPlayer)
target_link_libraries(videoPlayerApp PUBLIC viewVideoPlayer)


#GST_PLUGIN_PATH
