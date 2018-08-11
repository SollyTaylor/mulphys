#include "pnx_reader_stl.h"


pnx::pnx_reader_stl::pnx_reader_stl(QObject *parent)
    : pnx::ReaderBase (pnx::PNX_READER_STL_MODULE_NAME, parent)
{

}

pnx::ReaderBase *pnx::pnx_reader_stl::create_plugin(QObject *parent)
{
    return new pnx_reader_stl(parent);
}

pnx::GeometricalField *pnx::pnx_reader_stl::read(const QString &geometry_file_path)
{
    return nullptr;
}
