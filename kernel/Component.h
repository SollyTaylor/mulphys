#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>
#include "Common.h"
#include "ComponentBase.h"
#include "ComponentInterface.h"

namespace pnx {

class Component {
public:
    static pnx::ComponentBase* get(const QString& pluginPath);
};

};



#endif // COMPONENT_H
