#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include <QObject>
#include "Common.h"

namespace pnx {

class ComponentBase : public QObject
{
    Q_OBJECT
public:
    explicit ComponentBase(QObject *parent = nullptr);
};

};


#endif // COMPONENTBASE_H
