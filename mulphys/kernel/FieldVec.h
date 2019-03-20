#ifndef FIELDVEC_H
#define FIELDVEC_H

#include "Common.h"

namespace mphs {

class Geometry;
class FieldVec : public QObject
{
    Q_OBJECT
public:
    explicit FieldVec(QObject *parent);

signals:

public slots:

private:

    arma::vec  value_;

};


}


#endif // FIELDVEC_H
