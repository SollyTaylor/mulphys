#ifndef FIELD_H
#define FIELD_H

#include <QObject>
#include "Common.h"

namespace pnx {

enum FieldLocation {
    INTEGRAL,
    VERTEX_CENTERED,
    FACE_CENTERED,
    CELL_CENTERED
};

class Field : public QObject
{
    Q_OBJECT
public:
    explicit Field(QObject* parent);

private:
    // field properties
    QString field_name_;
    FieldLocation field_location_;

private:
    // field data
    arma::mat data;

};


}


#endif // FIELD_H
