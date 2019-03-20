#include "FieldTrait.h"


mphs::FieldTrait::FieldTrait(QObject *parent)
    : QObject(parent)
    , location_(mphs::FieldLocation::UndefinedLocation)
    , data_type_(mphs::FieldDataType::UndefinedDataType)
    , io_type_(mphs::FieldIOType::UndefinedIOType)
{

}

void mphs::FieldTrait::init(mphs::Configurator config)
{

}
