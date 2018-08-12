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

    QString config_json_path() const;

    QJsonObject config_default_obj() const;

    QJsonObject config_schema_obj() const;

    QJsonObject config_obj() const;

private:
    QString module_name_;

    QString config_json_path_;

    QJsonObject config_default_obj_;
    QJsonObject config_schema_obj_;
    QJsonObject config_obj_;


};

};


#endif // COMPONENTBASE_H
