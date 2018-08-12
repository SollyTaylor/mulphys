#include "Field.h"

mphs::Field::Field(QObject *parent)
    : QObject(parent)
    , field_traits_(new FieldTraits(parent))
{

}

