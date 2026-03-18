# QPlotTools

QPlotTools is a plotting widgets collection for Qt framework. This widget collection is designed to be header only.

## Including in Your Project

### CMake

You can use QPlotTools as a subdirectory or install it and use `find_package`.

**As a subdirectory:**
```cmake
add_subdirectory(qplottools)
target_link_libraries(your_target PRIVATE QPlotTools::QPlotTools)
```

**After installing:**
```cmake
find_package(QPlotTools REQUIRED)
target_link_libraries(your_target PRIVATE QPlotTools::QPlotTools)
```

**Building and installing:**
```sh
cmake -B build -DCMAKE_INSTALL_PREFIX=/your/install/path
cmake --build build
cmake --install build
```

Optionally build examples and tests:
```sh
cmake -B build -DQPLOTTOOLS_BUILD_EXAMPLES=ON -DQPLOTTOOLS_BUILD_TESTS=ON
```

### qmake

Include `qplottools.pri` from your `.pro` file:

```qmake
include(path/to/qplottools/qplottools.pri)
```