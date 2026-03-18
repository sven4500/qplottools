add_executable(graph2d
    main.cpp
    widget.cpp
)

target_link_libraries(graph2d PRIVATE
    QPlotTools::QPlotTools
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)
