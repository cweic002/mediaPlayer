cmake_minimum_required(VERSION 3.5)

project(iGstMediaPlayer VERSION 0.1 LANGUAGES CXX)

add_library(iGstMediaPlayer
    "iGstMediaPlayer.h"
    "iGstMediaPlayer.cpp"
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)

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

target_include_directories(iGstMediaPlayer PUBLIC ${gstreamer_INCLUDE_DIRS})
target_link_libraries(iGstMediaPlayer PRIVATE ${gstreamer_LIBRARIES})

target_link_libraries(iGstMediaPlayer PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(iGstMediaPlayer PUBLIC ${videoPlayerApp_SOURCE_DIR})
