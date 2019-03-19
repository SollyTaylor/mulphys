#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "Common.h"

class Geometry : public QObject
{
    Q_OBJECT
public:
    explicit Geometry(QObject *parent = nullptr);

signals:

public slots:

private:

    arma::umat  elements_;
    arma::mat   points_;

};

#endif // GEOMETRY_H
