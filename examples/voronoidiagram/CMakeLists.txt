add_executable(voronoidiagram
    main.cpp
)

target_link_libraries(voronoidiagram PRIVATE
    QPlotTools::QPlotTools
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)
