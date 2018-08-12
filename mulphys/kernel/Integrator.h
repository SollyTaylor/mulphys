#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "Common.h"
#include "IntegratorBase.h"
#include "IntegratorInterface.h"

namespace mphs {

class Integrator
{
public:
    static mphs::IntegratorBase* get(const QString& integrator_name, QObject* parent);
};

}


#endif // INTEGRATOR_H
