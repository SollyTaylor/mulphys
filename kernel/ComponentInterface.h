#ifndef COMPONENTINTERFACE_H
#define COMPONENTINTERFACE_H

#include "Common.h"
#include "ComponentBase.h"

namespace pnx {
class ComponentInterface
{
public:
    virtual pnx::ComponentBase* create_component(const QString& component_name = "") = 0;
    virtual ~ComponentInterface(){}

};
}

Q_DECLARE_INTERFACE(pnx::ComponentInterface, "pnx.component.interface")


#endif // COMPONENTINTERFACE_H
