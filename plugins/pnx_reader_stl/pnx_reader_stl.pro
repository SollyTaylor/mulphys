
QT       -= gui
QT       += core

TARGET = pnx_reader_stl
TEMPLATE = lib
CONFIG += plugin c++11

HEADERS += \
    pnx_reader_stl.h

SOURCES += \
    pnx_reader_stl.cpp

include($$(PANAX_ROOT)/projects/panax.pri)
include($$(PANAX_ROOT)/projects/armadillo.pri)

CONFIG(release, debug|release): DESTDIR = $$(PANAX_ROOT)/components/Release
CONFIG(debug, debug|release): DESTDIR = $$(PANAX_ROOT)/components/Debug

# DONNOT MOVE THIS LINE for $$PWD is located at the same direcotry as current *.pro file
target.files = $$PWD/*.json
target.path = $$DESTDIR
INSTALLS += target
