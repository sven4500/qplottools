cmake_minimum_required(VERSION 3.14)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(graph2d)
add_subdirectory(graphpolar)
add_subdirectory(gradientmap)
add_subdirectory(voronoidiagram)
