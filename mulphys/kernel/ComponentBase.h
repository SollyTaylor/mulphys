#ifndef COMPONENTBASE_H
#define COMPONENTBASE_H

#include <QObject>
#include "Common.h"

namespace mphs {

class ComponentBase : public QObject
{
    Q_OBJECT
public:
    explicit ComponentBase(const QString& module_name, QObject *parent = nullptr);
    virtual ~ComponentBase() {}

    QString module_name() const;

private:
    QString module_name_;
};

};


#endif // COMPONENTBASE_H
