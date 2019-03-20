#ifndef FIELD_H
#define FIELD_H

#include "Common.h"
#include "FieldTrait.h"

#include "FieldScalar.h"
#include "FieldVec.h"
#include "FieldUVec.h"
#include "FieldMat.h"

namespace mphs {

class Geometry;
class Field : public QObject
{
    Q_OBJECT
public:
    explicit Field(mphs::Geometry* geometry, QObject* parent);

private:

    FieldTrait* trait_;

private:

    Geometry* g_;

private:

    FieldScalar* s_;

    FieldVec* v_;
    FieldUVec* uv_;

    FieldMat* m_;




};


}


#endif // FIELD_H
