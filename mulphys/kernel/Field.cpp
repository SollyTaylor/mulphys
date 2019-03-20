#include "FieldBase.h"

mphs::FieldBase::FieldBase(mphs::Geometry *geometry, QObject *parent)
    : QObject(parent)
    , trait_(new FieldTrait(parent))
    , g_(geometry)
{

}
