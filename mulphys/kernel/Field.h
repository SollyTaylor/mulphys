#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include "Common.h"
#include "FieldTraits.h"

namespace mphs {

class Field : public QObject
{
    Q_OBJECT
public:
    explicit Field(QObject* parent);

private:

    FieldTraits* field_traits_;

private:

    double scalar_;

    arma::vec   vData_;
    arma::ivec  ivData_;
    arma::uvec  uvData_;

    arma::mat   mData_;
    arma::imat imData_;
    arma::umat umData_;

};


}


#endif // FIELD_H
