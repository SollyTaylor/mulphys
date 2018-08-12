#ifndef READERINTERFACE_H
#define READERINTERFACE_H

#include "Common.h"
#include "ReaderBase.h"

namespace pnx {

class ReaderInterface {
public:
    virtual pnx::ReaderBase* create_plugin(QObject* parent) = 0;
    virtual ~ReaderInterface(){}
};
}

Q_DECLARE_INTERFACE(pnx::ReaderInterface, "pnx.reader.interface")

#endif // READERINTERFACE_H
