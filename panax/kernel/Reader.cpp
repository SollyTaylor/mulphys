#include "Reader.h"

pnx::ReaderBase *pnx::Reader::get(const QString &reader_name, QObject *parent)
{
    return pnx::Common::get<pnx::ReaderInterface, pnx::ReaderBase>(reader_name, parent);
}
