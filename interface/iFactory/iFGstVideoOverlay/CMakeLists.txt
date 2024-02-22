cmake_minimum_required(VERSION 3.5)

project(iFGstVideoOverlay VERSION 0.1 LANGUAGES CXX)
add_library(iFGstVideoOverlay "iFGstVideoOverlay.h")

find_package(PkgConfig)

macro(find_gstreamer_component prefix pkg lib)
  pkg_check_modules(PC_${prefix} REQUIRED ${pkg})
  find_library(${prefix}_LIBRARIES NAMES ${lib} HINTS ${PC_${prefix}_LIBRARY_DIRS} ${PC_${prefix}_LIBDIR})
  list(APPEND gstreamer_INCLUDE_DIRS ${PC_${prefix}_INCLUDE_DIRS})
  list(APPEND gstreamer_LIBRARIES ${${prefix}_LIBRARIES})
  mark_as_advanced(${prefix}_LIBRARIES gstreamer_LIBRARIES gstreamer_INCLUDE_DIRS)
endmacro()

find_gstreamer_component(gstvideo gstreamer-video-1.0 gstvideo-1.0)

target_include_directories(iFGstVideoOverlay PUBLIC ${gstreamer_INCLUDE_DIRS})
target_link_libraries(iFGstVideoOverlay PRIVATE ${gstreamer_LIBRARIES})
