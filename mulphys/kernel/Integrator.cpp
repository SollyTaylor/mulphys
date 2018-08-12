#include "Integrator.h"

mphs::IntegratorBase *mphs::Integrator::get(const QString &integrator_name, QObject *parent)
{
    return mphs::Common::get<mphs::IntegratorInterface, mphs::IntegratorBase>(integrator_name, parent);
}
