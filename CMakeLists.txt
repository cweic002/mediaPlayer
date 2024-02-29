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

#find_gstreamer_component(gst      gstreamer-1.0       gstreamer-1.0)
# find_gstreamer_component(glib glib-2.0 glib-2.0)
# find_gstreamer_component(gstgobject gobject-2.0 gobject-2.0)
# find_gstreamer_component(gthread gstreamer-1.0 gthread-2.0)

#find_gstreamer_component(gstbase  gstreamer-base-1.0  gstbase-1.0)
#find_gstreamer_component(gstapp   gstreamer-app-1.0   gstapp-1.0)
#find_gstreamer_component(gstvideo gstreamer-video-1.0 gstvideo-1.0)
#find_gstreamer_component(glib glib-2.0 glib-2.0)
#find_gstreamer_component(gstgobject gobject-2.0 gobject-2.0)
find_gstreamer_component(gthread gstreamer-1.0 gthread-2.0)
#find_gstreamer_component(gstaudio gstreamer-audio-1.0 gstaudio-1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES videoPlayerApp_ru_RU.ts videoPlayerApp_en_US.ts)

add_subdirectory(interface)
add_subdirectory(plugin)
add_subdirectory(object)
add_subdirectory(widget)

set(PROJECT_SOURCES
    main.cpp
    videoPlayerApp.h
    videoPlayerApp.cpp
    videoPlayerApp.inl
    videoPlayerApp.ui
    videoPlayerApp.qrc
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(videoPlayerApp MANUAL_FINALIZATION ${PROJECT_SOURCES}
        videoPlayerApp_en_US.ts)
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET untitled APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
    #qt_add_translations(videoPlayerApp TS_FILES videoPlayerApp_ru_RU.ts)
    # qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    # qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    # qt_add_lupdate(videoPlayerApp TS_FILES videoPlayerApp_ru_RU.ts)
    # qt_add_translations(videoPlayerApp TS_FILES videoPlayerApp_ru_RU.ts)

    qt_add_lupdate(videoPlayerApp
        TS_FILES
        ${TS_FILES})
    qt_add_lrelease(videoPlayerApp
        TS_FILES ${TS_FILES}
        QM_FILES_OUTPUT_VARIABLE qm_files)
    qt_add_resources(videoPlayerApp "translations"
        PREFIX "/i18n"
        BASE "${CMAKE_CURRENT_BINARY_DIR}"
        FILES "${qm_files}")
else()
    if(ANDROID)
        add_library(videoPlayerApp SHARED ${PROJECT_SOURCES})
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(videoPlayerApp ${PROJECT_SOURCES})
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(videoPlayerApp PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# target_link_libraries(videoPlayerApp PRIVATE ${gstreamer_LIBRARIES})
# include_directories(${gstreamer_INCLUDE_DIRS})

set_target_properties(videoPlayerApp PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(videoPlayerApp PUBLIC objectFGstVideoPlayer)
target_link_libraries(videoPlayerApp PUBLIC widgetBotomMenuPlayer)
target_link_libraries(videoPlayerApp PUBLIC widgetContexMenu)

include(GNUInstallDirs)
install(TARGETS videoPlayerApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(videoPlayerApp)
endif()

#GST_PLUGIN_PATH
