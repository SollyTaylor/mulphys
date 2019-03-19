#include "Consensus.h"


mphs::Consensus::Consensus(QObject *parent)
    : QObject(parent)
    , location_(mphs::FieldLocation::UndefinedLocation)
    , data_type_(mphs::FieldDataType::UndefinedDataType)
    , io_type_(mphs::FieldIOType::UndefinedIOType)
{

}

void mphs::Consensus::init(mphs::Configurator config)
{

}
