#ifndef GEOMETRICALFIELD_H
#define GEOMETRICALFIELD_H

#include "Common.h"
#include "Field.h"
#include "FieldTraits.h"

namespace mphs {
class GeometricalField : public QObject
{
    Q_OBJECT
public:
    explicit GeometricalField(const QString& geometrical_field_name,
                              QObject *parent);

    QString geometrical_field_name() const;

private:

    /// compulsory fields
    ///
    /// vertices, n x 3
    /// faces, m x k
    /// vocc, vertices occurrences in elements, n x p
    /// neighbors
    /// sectionIndices
    ///
    QMap<FieldKey, mphs::Field*> fields_;

    QString geometrical_field_name_;

};
}


#endif // GEOMETRICALFIELD_H
