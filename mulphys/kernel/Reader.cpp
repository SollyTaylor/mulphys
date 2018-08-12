#include "Reader.h"

mphs::ReaderBase *mphs::Reader::get(const QString &reader_name, QObject *parent)
{
    return mphs::Common::get<mphs::ReaderInterface, mphs::ReaderBase>(reader_name, parent);
}
