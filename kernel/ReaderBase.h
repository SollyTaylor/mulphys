#ifndef READERBASE_H
#define READERBASE_H

#include "Common.h"
#include "ComponentBase.h"

namespace pnx {

class ReaderBase : public ComponentBase
{
    Q_OBJECT
public:
    explicit ReaderBase(QObject* parent);

signals:

public slots:
};


}

#endif // READERBASE_H
