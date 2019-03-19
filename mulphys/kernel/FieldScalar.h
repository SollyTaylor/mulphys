#ifndef FIELDSCALAR_H
#define FIELDSCALAR_H

#include "FieldBase.h"

namespace mphs {

class Geometry;
class FieldScalar : public FieldBase
{
    Q_OBJECT
public:
    explicit FieldScalar(Geometry* g, QObject* parent);

signals:

public slots:

private:

    double value_;

};

}


#endif // FIELDSCALAR_H
