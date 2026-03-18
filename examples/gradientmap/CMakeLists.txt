add_executable(gradientmap
    main.cpp
    widget.cpp
)

target_link_libraries(gradientmap PRIVATE
    QPlotTools::QPlotTools
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)
