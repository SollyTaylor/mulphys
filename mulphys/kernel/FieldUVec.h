#ifndef FIELDUVEC_H
#define FIELDUVEC_H

#include "Common.h"

class FieldUVec : public QObject
{
    Q_OBJECT
public:
    explicit FieldUVec(QObject *parent = nullptr);

signals:

public slots:

private:

    arma::uvec value_;
};

#endif // FIELDUVEC_H
