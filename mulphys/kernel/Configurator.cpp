#include "Configurator.h"


mphs::Configurator::Configurator(QJsonObject schema, QObject *parent)
    : QObject(parent)
    , schema_(schema)
{

}

QJsonObject mphs::Configurator::config() const
{
    return config_;
}

void mphs::Configurator::setConfig(const QJsonObject &config)
{
    config_ = config;
    THROW_MPHSEXCEPTION_INFO("检查是否满足config");
}
