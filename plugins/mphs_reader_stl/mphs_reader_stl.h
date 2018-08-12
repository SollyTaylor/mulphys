#ifndef MPHS_READER_STL_H
#define MPHS_READER_STL_H

#include "Common.h"
#include "GeometricalField.h"

#include "ReaderBase.h"
#include "ReaderInterface.h"
#include "ComponentBase.h"

namespace mphs {

const QString MPHS_READER_STL_MODULE_NAME = "mphs_reader_stl";

class mphs_reader_stl :
        public mphs::ReaderBase,
        public mphs::ReaderInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "mphs_reader_stl.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(mphs::ReaderInterface)
public:
    mphs_reader_stl(QObject* parent = nullptr);
    virtual ~mphs_reader_stl(){}

    mphs::ReaderBase* create_plugin(QObject* parent);

    mphs::GeometricalField *read(const QString& geometry_file_path);

};

}

#endif // MPHS_READER_STL_H
