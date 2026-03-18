find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Test Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Test Widgets)

set(CMAKE_AUTOMOC ON)

add_executable(testgraph2d
    testgraph2d.cpp
)

target_link_libraries(testgraph2d PRIVATE
    QPlotTools::QPlotTools
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Test
    Qt${QT_VERSION_MAJOR}::Widgets
)

add_test(NAME testgraph2d COMMAND testgraph2d)
