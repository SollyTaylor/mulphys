#include "FieldTraits.h"


mphs::FieldTraits::FieldTraits(QObject *parent)
    : QObject(parent)
    , location_(mphs::FieldLocation::UndefinedLocation)
    , data_type_(mphs::FieldDataType::UndefinedDataType)
    , io_type_(mphs::FieldIOType::UndefinedIOType)
{

}

void mphs::FieldTraits::init(mphs::Configurator config)
{

}
