cmake_minimum_required(VERSION 3.5)

project(Teapot VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_compile_definitions(FIND_FILES="${CMAKE_CURRENT_SOURCE_DIR}")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Teapot
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        renderview.h renderview.cpp
        rendermain.h rendermain.cpp
        Rendering/scene.h Rendering/scene.cpp
        Rendering/raytracer.h Rendering/raytracer.cpp
        Rendering/Breakdown.md
        Rendering/Core/ray.h
        Rendering/Core/camera.h
        Rendering/Core/onb.h Rendering/Core/onb.cpp
        Rendering/Core/rgba.h
        Rendering/Core/rng.h
        Rendering/Objects/shape.h
        Rendering/Objects/sphere.h Rendering/Objects/sphere.cpp
        Rendering/Shaders/shader.h
        Rendering/Shaders/light.h
        Rendering/Shaders/texture.h Rendering/Shaders/texture.cpp
        Rendering/Objects/plane.h Rendering/Objects/plane.cpp
        Rendering/Shaders/shader.cpp
        Rendering/Objects/bbox.h Rendering/Objects/bbox.cpp
        Rendering/Objects/triangle.h Rendering/Objects/triangle.cpp
        Rendering/Objects/trianglegroup.h Rendering/Objects/trianglegroup.cpp

        Rendering/trianglereader.h Rendering/trianglereader.cpp
        Rendering/Shaders/solidnoise.h Rendering/Shaders/solidnoise.cpp
        Rendering/Shaders/noiseshader.h Rendering/Shaders/noiseshader.cpp
        Rendering/Shaders/marbleshader.h Rendering/Shaders/marbleshader.cpp
        Rendering/Shaders/brickwallshader.h Rendering/Shaders/brickwallshader.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Teapot APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Teapot SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Teapot
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Teapot PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Teapot)
endif()
set_target_properties(Teapot PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Teapot
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Teapot)
endif()
