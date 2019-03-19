#ifndef GEOMETRICALFIELD_H
#define GEOMETRICALFIELD_H

#include "Common.h"
#include "FieldBase.h"
#include "Consensus.h"

namespace mphs {

class Geometry;
class GeometricalField : public QObject
{
    Q_OBJECT
public:
    explicit GeometricalField(const QString& geometrical_field_name,
                              QObject *parent);

    QString geometrical_field_name() const;

    static void save(const GeometricalField* gf, const QString& file_path);

    static mphs::GeometricalField* load(const QString& file_path);

private:

    QMap<FieldKey, mphs::FieldBase*> fields_;
    Geometry* g_;

    QString geometrical_field_name_;

};
}


#endif // GEOMETRICALFIELD_H
