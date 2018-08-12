#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "Common.h"

namespace mphs {


class Configurator : public QObject
{
    Q_OBJECT
public:
    explicit Configurator(QJsonObject schema, QObject* parent);

    QJsonObject config() const;
    void setConfig(const QJsonObject &config);

private:
    QJsonObject schema_;
    QJsonObject config_;

};
}



#endif // CONFIGURATOR_H
