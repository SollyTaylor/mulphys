#ifndef FIELDTRAITS_H
#define FIELDTRAITS_H

#include "Common.h"
#include "Configurator.h"

namespace mphs {

class FieldTraits : public QObject
{
    Q_OBJECT
public:
    explicit FieldTraits(QObject *parent = nullptr);
    virtual ~FieldTraits(){}

    void init(Configurator config);

private:

    // field properties
    QString name_;
    QString description_;

    // where the physical data located
    FieldLocation location_;

    // activated field data type
    FieldDataType data_type_;

    FieldIOType io_type_;

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



#endif // FIELDTRAITS_H
