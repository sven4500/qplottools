add_executable(graphpolar
    main.cpp
)

target_link_libraries(graphpolar PRIVATE
    QPlotTools::QPlotTools
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)
