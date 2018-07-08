#-------------------------------------------------
#
# Project created by QtCreator 2015-09-10T12:22:23
#
#-------------------------------------------------

QT       -= gui
QT       += core

TARGET = tsplib
TEMPLATE = lib
CONFIG += staticlib c++11

include($$(TSP_ROOT)/projects/build_type_layout.pri)
include($$(TSP_ROOT)/projects/curl.pri)
include($$(TSP_ROOT)/projects/armadillo.pri)

DEFINES += QT_USE_QSTRINGBUILDER

win32: {
    DEFINES += NOMINMAX
    INCLUDEPATH += include/tsp \
        $$(TSP_ROOT)/thirdparties/sole/sole \
        $$(TSP_ROOT)/thirdparties/QtVerbalExpressions\QtVerbalExpressions \
        $$(TSP_ROOT)/include/strtk
}

unix: !macx: {
    INCLUDEPATH += include/tsp \
        $$(TSP_ROOT)/thirdparties/sole/sole \
        $$(TSP_ROOT)/thirdparties/QtVerbalExpressions\QtVerbalExpressions \
        $$(TSP_ROOT)/include/strtk
}

macx: {
    INCLUDEPATH += include/tsp \
        $$(TSP_ROOT)/thirdparties/sole/sole \
        $$(TSP_ROOT)/thirdparties/QtVerbalExpressions\QtVerbalExpressions \
        $$(TSP_ROOT)/include/strtk
}

include($$(TSP_ROOT)/projects/jsoncpp.pri)
include($$(TSP_ROOT)/projects/lapack.pri)
include($$(TSP_ROOT)/projects/boost.pri)

SOURCES += \
    src/tsp/GeometryBar2.cpp \
    src/tsp/GeometryBase.cpp \
    src/tsp/GeometryHelperBase.cpp \
    src/tsp/GeometryHexa8.cpp \
    src/tsp/GeometryMixed34.cpp \
    src/tsp/GeometryMixed34Helper.cpp \
    src/tsp/GeometryNode1.cpp \
    src/tsp/GeometryPolygN.cpp \
    src/tsp/GeometryPolyhN.cpp \
    src/tsp/GeometryQuad4.cpp \
    src/tsp/GeometryQuad4Helper.cpp \
    src/tsp/GeometryReaderBase.cpp \
    src/tsp/GeometryTet4.cpp \
    src/tsp/GeometryTria3.cpp \
    src/tsp/GeometryTria3Helper.cpp \
    src/tsp/SurfaceSectionsPack.cpp \
    src/tsp/Sys.cpp \
    src/tsp/TimeAxis.cpp \
    src/tsp/Utilities.cpp \
    src/tsp/VerticesPack.cpp \
    src/tsp/GeometricalField.cpp \
    src/tsp/SysQt.cpp \
    src/tsp/SolverBase.cpp \
    src/tsp/GeometryReader.cpp \
    src/tsp/Solver.cpp \
    src/tsp/ResourceBase.cpp \
    src/tsp/Resource.cpp \
    src/tsp/version_number.cpp \
    src/tsp/SysQtEx.cpp \
    src/tsp/Environment.cpp \
    src/tsp/EnvironmentBase.cpp \
    src/tsp/Material.cpp \
    src/tsp/MaterialBase.cpp \
    src/tsp/db.cpp \
    src/tsp/Dynamics.cpp \
    src/tsp/DynamicsBase.cpp \
    src/tsp/Integrator.cpp \
    src/tsp/IntegratorBase.cpp \
    src/tsp/armadillo_aux.cpp \
    src/tsp/CodeStream.cpp \
    src/tsp/GeometricalFieldProperties.cpp \
    src/tsp/Provider.cpp \
    src/tsp/ProviderBase.cpp \
    src/tsp/Serializer.cpp \
    src/tsp/Writer.cpp \
    src/tsp/WriterBase.cpp \
    src/tsp/WorkingRange.cpp \
    src/tsp/Interpolator.cpp \
    src/tsp/InterpolatorBase.cpp \
    src/tsp/KDSpace.cpp \
    src/tsp/KD_ST_Space.cpp \
    src/tsp/KD_UN_Space.cpp \
    src/tsp/BatchBase.cpp \
    src/tsp/Batch.cpp \
    src/tsp/Channel.cpp \
    src/tsp/Connector.cpp \
    src/tsp/ConnectorBase.cpp \
    src/tsp/Recorder.cpp \
    src/tsp/RecorderBase.cpp \
    src/tsp/Controller.cpp \
    src/tsp/ControllerBase.cpp \
    src/tsp/Peripheral.cpp \
    src/tsp/Model.cpp \
    src/tsp/ModelBase.cpp \
    src/tsp/SimulationBase.cpp \
    src/tsp/SimulationUnit.cpp \
    src/tsp/SimulationWrapper.cpp \
    src/tsp/SimulationSeparator.cpp \
    src/tsp/Simulation.cpp \
    src/tsp/SimulationParseHelper.cpp \
    src/tsp/SimulationParseHelperUnit.cpp \
    src/tsp/SimulationParseHelperWrapper.cpp \
    src/tsp/SimulationParseHelperSeparator.cpp \
    src/tsp/RecursiveSequence.cpp \
    src/tsp/tsptypes.cpp \
    $$(TSP_ROOT)/thirdparties/QtVerbalExpressions/QtVerbalExpressions/QVerbalExpressions.cpp \
    src/tsp/Evaluator.cpp \
    src/tsp/EvaluatorBase.cpp \
    src/tsp/Analyzer.cpp \
    src/tsp/AnalyzerBase.cpp \
    src/tsp/SolutionExtractionEngine.cpp

HEADERS += \
    include/tsp/Common.h \
    include/tsp/Exceptions.h \
    include/tsp/Geometry.h \
    include/tsp/GeometryBar2.h \
    include/tsp/GeometryBase.h \
    include/tsp/GeometryHelperBase.h \
    include/tsp/GeometryHexa8.h \
    include/tsp/GeometryMixed34.h \
    include/tsp/GeometryMixed34Helper.h \
    include/tsp/GeometryNode1.h \
    include/tsp/GeometryPolygN.h \
    include/tsp/GeometryPolyhN.h \
    include/tsp/GeometryQuad4.h \
    include/tsp/GeometryQuad4Helper.h \
    include/tsp/GeometryReaderBase.h \
    include/tsp/GeometryTet4.h \
    include/tsp/GeometryTria3.h \
    include/tsp/GeometryTria3Helper.h \
    include/tsp/MeshSlim.h \
    include/tsp/SurfaceSectionsPack.h \
    include/tsp/Sys.h \
    include/tsp/TimeAxis.h \
    include/tsp/tsp.h \
    include/tsp/Utilities.h \
    include/tsp/VerticesPack.h \
    include/tsp/SolverBase.h \
    include/tsp/GeometricalField.h \
    include/tsp/SysQt.h \
    include/tsp/SolverInterface.h \
    include/tsp/GeometryReaderInterface.h \
    include/tsp/GeometryReader.h \
    include/tsp/Solver.h \
    include/tsp/Resource.h \
    include/tsp/ResourceBase.h \
    include/tsp/ResourceInterface.h \
    include/tsp/version_number.h \
    include/tsp/SysQtEx.h \
    include/tsp/Environment.h \
    include/tsp/EnvironmentBase.h \
    include/tsp/EnvironmentInterface.h \
    include/tsp/Material.h \
    include/tsp/MaterialBase.h \
    include/tsp/MaterialInterface.h \
    include/tsp/db.h \
    include/tsp/Dynamics.h \
    include/tsp/DynamicsBase.h \
    include/tsp/DynamicsInterface.h \
    include/tsp/Integrator.h \
    include/tsp/IntegratorBase.h \
    include/tsp/IntegratorInterface.h \
    include/tsp/armadillo_aux.h \
    include/tsp/exprtk.hpp \
    include/tsp/CodeStream.h \
    include/tsp/GeometricalFieldProperties.h \
    include/tsp/Provider.h \
    include/tsp/ProviderInterface.h \
    include/tsp/ProviderBase.h \
    include/tsp/Serializer.h \
    include/tsp/Writer.h \
    include/tsp/WriterBase.h \
    include/tsp/WriterInterface.h \
    include/tsp/MeshSlim2.h \
    include/tsp/WorkingRange.h \
    include/tsp/Interpolator.h \
    include/tsp/InterpolatorBase.h \
    include/tsp/InterpolatorInterface.h \
    include/tsp/Batch.h \
    include/tsp/BatchBase.h \
    include/tsp/BatchInterface.h \
    include/tsp/KDSpace.h \
    include/tsp/Channel.h \
    include/tsp/Connector.h \
    include/tsp/ConnectorBase.h \
    include/tsp/ConnectorInterface.h \
    include/tsp/Recorder.h \
    include/tsp/RecorderBase.h \
    include/tsp/RecorderInterface.h \
    include/tsp/ControllerInterface.h \
    include/tsp/ControllerBase.h \
    include/tsp/Controller.h \
    include/tsp/Peripheral.h \
    include/tsp/Model.h \
    include/tsp/ModelBase.h \
    include/tsp/ModelInterface.h \
    include/tsp/tsptypes.h \
    include/tsp/tsp_win_platform.h \
    include/tsp/SimulationBase.h \
    include/tsp/SimulationUnit.h \
    include/tsp/SimulationWrapper.h \
    include/tsp/SimulationSeparator.h \
    include/tsp/Simulation.h \
    include/tsp/TimeMacros.h \
    include/tsp/SimulationParseHelper.h \
    include/tsp/RecursiveSequence.h \
    include/tsp/NativeServerTalker.h \
    include/tsp/Evaluator.h \
    include/tsp/EvaluatorBase.h \
    include/tsp/EvaluatorInterface.h \
    include/tsp/Analyzer.h \
    include/tsp/AnalyzerBase.h \
    include/tsp/AnalyzerInterface.h \
    include/tsp/SolutionExtractionEngine.h

# define the installation destination directory
win32 :{
    !contains(QMAKE_TARGET.arch, x86_64) {
    # not x64
        message("x86 build for tsplib")
        CONFIG(release, debug|release): DESTDIR = $$(TSP_ROOT)/lib/x86/win/Release
        CONFIG(debug, debug|release): DESTDIR = $$(TSP_ROOT)/lib/x86/win/Debug
        ## Windows x86 (32bit) specific build here
    } else {
        message("x64 build for tsplib")
        CONFIG(release, debug|release): DESTDIR = $$(TSP_ROOT)/lib/x64/win/Release
        CONFIG(debug, debug|release): DESTDIR = $$(TSP_ROOT)/lib/x64/win/Debug
    }

}

unix: !macx: {
    CONFIG(release, debug|release): DESTDIR = $$(TSP_ROOT)/lib/x64/lnx/Release
    CONFIG(debug, debug|release): DESTDIR = $$(TSP_ROOT)/lib/x64/lnx/Debug
# for usage of sole/uuid generator
    LIBS += -lrt
}

macx :{
    CONFIG(release, debug|release): DESTDIR = $$(TSP_ROOT)/lib/x64/osx/Release
    CONFIG(debug, debug|release): DESTDIR = $$(TSP_ROOT)/lib/x64/osx/Debug
}


tsplibinstall.files = $$OUT_PWD/libtsplib.a
tsplibinstall.path = $$DESTDIR
INSTALLS += tsplibinstall

# once the DESTDIR is assigned, it can not be changed for another path, as a result,
# the other destination directories need to be set as relative directories

tsplibincludes.files = $$PWD/include/tsp/*
tsplibincludes.path = $$DESTDIR/../../../../include/tsp
INSTALLS += tsplibincludes

