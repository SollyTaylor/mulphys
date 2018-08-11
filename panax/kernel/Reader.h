
#ifndef READER_H
#define READER_H

#include "Common.h"
#include "ReaderBase.h"
#include "ReaderInterface.h"

namespace pnx {

class Reader
{
public:
    static pnx::ReaderBase* get(const QString& reader_name, QObject* parent);
};

}



#endif // READER_H
