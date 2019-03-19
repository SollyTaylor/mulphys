#include "GeometricalField.h"

mphs::GeometricalField::GeometricalField(const QString& geometrical_field_name, QObject *parent)
    : QObject(parent)
    , geometrical_field_name_(geometrical_field_name)
{

}

QString mphs::GeometricalField::geometrical_field_name() const
{
    return geometrical_field_name_;
}
