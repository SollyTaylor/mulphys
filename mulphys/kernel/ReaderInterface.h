#ifndef READERINTERFACE_H
#define READERINTERFACE_H

#include "Common.h"
#include "ReaderBase.h"

namespace mphs {

class ReaderInterface {
public:
    virtual mphs::ReaderBase* create_plugin(QObject* parent) = 0;
    virtual ~ReaderInterface(){}
};
}

Q_DECLARE_INTERFACE(mphs::ReaderInterface, "mphs.reader.interface")

#endif // READERINTERFACE_H
