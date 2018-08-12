
QT       -= gui
QT       += core

TARGET = mphs_processor_exprtk
TEMPLATE = lib
CONFIG += plugin c++11

HEADERS += \
    mphs_processor_exprtk.h

SOURCES += \
    mphs_processor_exprtk.cpp

include($$(MULPHYS_ROOT)/projects/mulphys.pri)
include($$(MULPHYS_ROOT)/projects/armadillo.pri)
include($$(MULPHYS_ROOT)/projects/rapidjson.pri)

CONFIG(release, debug|release): DESTDIR = $$(MULPHYS_ROOT)/components/Release
CONFIG(debug, debug|release): DESTDIR = $$(MULPHYS_ROOT)/components/Debug

# DONNOT MOVE THIS LINE for $$PWD is located at the same direcotry as current *.pro file
target.files = $$PWD/*.json
target.path = $$DESTDIR
INSTALLS += target
