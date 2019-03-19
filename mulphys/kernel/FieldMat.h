#ifndef FIELDMAT_H
#define FIELDMAT_H

#include "FieldBase.h"

namespace mphs {

class FieldMat : public FieldBase
{
    Q_OBJECT
public:

    explicit FieldMat(Geometry* g, QObject *parent);

signals:

public slots:

private:

    arma::mat value_;
};

}


#endif // FIELDMAT_H
