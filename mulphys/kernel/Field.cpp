#include "Field.h"

mphs::Field::Field(mphs::Geometry *geometry, QObject *parent)
    : QObject(parent)
    , trait_(new FieldTrait(parent))
    , g_(geometry)
{

}
