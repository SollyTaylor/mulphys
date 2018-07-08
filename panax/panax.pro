#-------------------------------------------------
#
# Project created by QtCreator 2015-09-28T23:43:57
#
#-------------------------------------------------

QT       += core

#QT       += gui declarative
#QT       += widgets

TARGET = tsp
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    tsp.cpp \
    tsp_runner.cpp

INCLUDEPATH += \
        include/tclap-1.2.1/include\
        ../tsplib/include/tsp\
        ../tsp_thirdparties/armadillo/armadillo-7.950.0/include


include($$(TSP_ROOT)/projects/tsp.pri)
include($$(TSP_ROOT)/projects/include.pri)
include($$(TSP_ROOT)/projects/jsoncpp.pri)
include($$(TSP_ROOT)/projects/lapack.pri)

HEADERS += \
    tsp_runner.h

    CONFIG(release, debug|release): DESTDIR = $$(TSP_ROOT)/bin/Release
    CONFIG(debug, debug|release): DESTDIR = $$(TSP_ROOT)/bin/Debug

win32: {
    tspinstall.files = $$OUT_PWD/tsp
    tspinstall.path = $$DESTDIR
    tspinstall.commands = $$PWD/rename_tsp.bat
    INSTALLS += tspinstall
}

unix: !macx: {
    tspinstall.files = $$OUT_PWD/tsp
    tspinstall.path = $$DESTDIR
    tspinstall.commands = $$PWD/rename_tsp.sh
    INSTALLS += tspinstall
}

macx :{
    tspinstall.files = $$OUT_PWD/tsp
    tspinstall.path = $$DESTDIR
    tspinstall.commands = sh $$PWD/rename_tsp.sh
    INSTALLS += tspinstall
}



#QMAKE_POST_LINK += $$PWD/rename_tsp.sh
