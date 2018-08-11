#ifndef READERBASE_H
#define READERBASE_H

#include "Common.h"
#include "ComponentBase.h"
#include "GeometricalField.h"

namespace pnx {

class ReaderBase : public ComponentBase
{
    Q_OBJECT
public:
    explicit ReaderBase(const QString& module_name, QObject* parent);

    virtual pnx::GeometricalField *read(const QString& geometry_file_path) = 0;

};


}

#endif // READERBASE_H
