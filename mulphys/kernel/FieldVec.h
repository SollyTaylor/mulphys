#ifndef FIELDVEC_H
#define FIELDVEC_H

#include "FieldBase.h"

namespace mphs {

class Geometry;
class FieldVec : public FieldBase
{
    Q_OBJECT

public:

    explicit FieldVec(Geometry* g, QObject* parent);

private:

    arma::vec value_;

};

}


#endif // FIELDVEC_H
