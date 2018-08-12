#ifndef INTEGRATORINTERFACE_H
#define INTEGRATORINTERFACE_H

#include "Common.h"
#include "IntegratorBase.h"

namespace mphs {

class IntegratorInterface {
public:
    virtual mphs::IntegratorBase* create_plugin(QObject* parent) = 0;
    virtual ~IntegratorInterface(){}
};
}

Q_DECLARE_INTERFACE(mphs::IntegratorInterface, "mphs.integrator.interface")


#endif // INTEGRATORINTERFACE_H
