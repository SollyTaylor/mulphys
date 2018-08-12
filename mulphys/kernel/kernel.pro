QT -= gui
QT += core

TEMPLATE = lib
CONFIG += staticlib c++11

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

include($$(MULPHYS_ROOT)/projects/armadillo.pri)

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    ComponentBase.cpp \
    Common.cpp \
    ReaderBase.cpp \
    Reader.cpp \
    GeometricalField.cpp \
    Field.cpp

HEADERS += \
    ComponentBase.h \
    Common.h \
    ReaderBase.h \
    Reader.h \
    ReaderInterface.h \
    GeometricalField.h \
    Field.h

win32: {
    TARGET = mulphys_kernel_win_x64
}

CONFIG(release, debug|release): DESTDIR = $$(MULPHYS_ROOT)/lib/Release
CONFIG(debug, debug|release): DESTDIR = $$(MULPHYS_ROOT)/lib/Debug

win32 :{
    target.path = $$DESTDIR
    INSTALLS += target
}
