#ifndef INTEGRATORBASE_H
#define INTEGRATORBASE_H

#include "Common.h"
#include "ComponentBase.h"

namespace mphs {

class IntegratorBase : public ComponentBase
{
    Q_OBJECT
public:
    explicit IntegratorBase(const QString& module_name, QObject* parent);

    virtual void integrate(const QString& geometry_file_path) = 0;

    virtual ~IntegratorBase(){}

};

}


#endif // INTEGRATORBASE_H
