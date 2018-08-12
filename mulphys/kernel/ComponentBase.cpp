#include "ComponentBase.h"

mphs::ComponentBase::ComponentBase(const QString &module_name, QObject *parent)
    : QObject(parent)
    , module_name_(module_name)
{
    config_json_path_ = mphs::Common::get_plugin_json_path(module_name);
    QJsonObject config_obj = mphs::Common::read_json_file_object(config_json_path_);

//    mphs::Common::check_is_json_object(config_obj, "config");
//    mphs::Common::check_is_json_object(config_obj, "config_schema");

//    config_default_obj_ = config_obj["config"].toObject();
//    config_schema_obj_ = config_obj["config_schema"].toObject();

//    mphs::Common::check_json_schema(config_default_obj_, config_schema_obj_);
}

QString mphs::ComponentBase::module_name() const
{
    return module_name_;
}

QJsonObject mphs::ComponentBase::config_obj() const
{
    return config_obj_;
}

QJsonObject mphs::ComponentBase::config_schema_obj() const
{
    return config_schema_obj_;
}

QJsonObject mphs::ComponentBase::config_default_obj() const
{
    return config_default_obj_;
}

QString mphs::ComponentBase::config_json_path() const
{
    return config_json_path_;
}
