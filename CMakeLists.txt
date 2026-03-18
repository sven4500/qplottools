cmake_minimum_required(VERSION 3.14)

project(QPlotTools VERSION 1.0.0 LANGUAGES CXX)

# Find Qt (supports both Qt5 and Qt6)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

# Create the INTERFACE library target (header-only)
add_library(QPlotTools INTERFACE)
add_library(QPlotTools::QPlotTools ALIAS QPlotTools)

target_include_directories(QPlotTools INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:include/QPlotTools>
)

target_link_libraries(QPlotTools INTERFACE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_compile_features(QPlotTools INTERFACE cxx_std_11)

# Installation rules
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(TARGETS QPlotTools
    EXPORT QPlotToolsTargets
)

install(DIRECTORY src/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QPlotTools
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT QPlotToolsTargets
    FILE QPlotToolsTargets.cmake
    NAMESPACE QPlotTools::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QPlotTools
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/QPlotToolsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/QPlotToolsConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QPlotTools
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/QPlotToolsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/QPlotToolsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/QPlotToolsConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QPlotTools
)

# Optionally build examples and tests
option(QPLOTTOOLS_BUILD_EXAMPLES "Build QPlotTools examples" OFF)
option(QPLOTTOOLS_BUILD_TESTS "Build QPlotTools tests" OFF)

if(QPLOTTOOLS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(QPLOTTOOLS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
