# QPlotTools - header-only plotting widget collection for Qt
# Include this file from your .pro project to use QPlotTools:
#
#   include(path/to/qplottools.pri)

QPLOTTOOLS_SRCDIR = $$PWD/src

INCLUDEPATH += $$QPLOTTOOLS_SRCDIR

HEADERS += $$files($$QPLOTTOOLS_SRCDIR/*.h)
