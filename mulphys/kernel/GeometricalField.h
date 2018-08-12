#ifndef GEOMETRICALFIELD_H
#define GEOMETRICALFIELD_H

#include "Common.h"
#include "Field.h"

namespace mphs {
class GeometricalField : public QObject
{
    Q_OBJECT
public:
    explicit GeometricalField(QObject *parent);

private:

    QMap<QString, mphs::Field*> fields_;

};
}


#endif // GEOMETRICALFIELD_H
