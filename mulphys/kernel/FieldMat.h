#ifndef FIELDMAT_H
#define FIELDMAT_H

#include "Common.h"

namespace mphs {

class FieldMat : public QObject
{
    Q_OBJECT
public:

    explicit FieldMat(QObject *parent);

signals:

public slots:

private:
    arma::mat  m_;
};

}


#endif // FIELDMAT_H
