#include "ComponentBase.h"

pnx::ComponentBase::ComponentBase(const QString &module_name,
                                  QObject *parent)
    : QObject(parent)
    , module_name_(module_name)
{

}

QString pnx::ComponentBase::module_name() const
{
    return module_name_;
}
