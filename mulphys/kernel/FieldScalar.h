#ifndef FIELDSCALAR_H
#define FIELDSCALAR_H

#include "Common.h"

namespace mphs {

class FieldScalar : public QObject
{
    Q_OBJECT
public:
    explicit FieldScalar(QObject* parent);

signals:

public slots:

private:

    double value_;

};

}


#endif // FIELDSCALAR_H
