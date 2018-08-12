#include "mphs_reader_stl.h"


mphs::mphs_reader_stl::mphs_reader_stl(QObject *parent)
    : mphs::ReaderBase (mphs::MPHS_READER_STL_MODULE_NAME, parent)
{

}

mphs::ReaderBase *mphs::mphs_reader_stl::create_plugin(QObject *parent)
{
    return new mphs_reader_stl(parent);
}

mphs::GeometricalField *mphs::mphs_reader_stl::read(const QString &geometry_file_path)
{
    return nullptr;
}
