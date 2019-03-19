#include "FieldBase.h"

mphs::FieldBase::FieldBase(mphs::Geometry *geometry, QObject *parent)
    : QObject(parent)
    , consensus_(new Consensus(parent))
    , g_(geometry)
{

}
