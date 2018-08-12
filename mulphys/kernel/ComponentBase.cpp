#include "ComponentBase.h"

mphs::ComponentBase::ComponentBase(const QString &module_name,
                                  QObject *parent)
    : QObject(parent)
    , module_name_(module_name)
{

}

QString mphs::ComponentBase::module_name() const
{
    return module_name_;
}
