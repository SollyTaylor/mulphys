#ifndef FIELD_H
#define FIELD_H

#include "Common.h"
#include "Consensus.h"

namespace mphs {

class Geometry;
class FieldBase : public QObject
{
    Q_OBJECT
public:
    explicit FieldBase(mphs::Geometry* geometry, QObject* parent);

private:

    Consensus* consensus_;

private:

    Geometry* g_;

};


}


#endif // FIELD_H
