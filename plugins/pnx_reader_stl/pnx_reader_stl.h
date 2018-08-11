#ifndef PNX_READER_STL_H
#define PNX_READER_STL_H

#include "Common.h"
#include "GeometricalField.h"

#include "ReaderBase.h"
#include "ReaderInterface.h"
#include "ComponentBase.h"

namespace pnx {

const QString PNX_READER_STL_MODULE_NAME = "pnx_reader_stl";

class pnx_reader_stl :
        public pnx::ReaderBase,
        public pnx::ReaderInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "pnx_reader_stl.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(pnx::ReaderInterface)
public:
    pnx_reader_stl(QObject* parent = nullptr);
    virtual ~pnx_reader_stl(){}

    pnx::ReaderBase* create_plugin(QObject* parent);

    pnx::GeometricalField *read(const QString& geometry_file_path);

};

}

#endif // PNX_READER_STL_H
