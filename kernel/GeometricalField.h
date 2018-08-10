#ifndef GEOMETRICALFIELD_H
#define GEOMETRICALFIELD_H

#include "Common.h"
#include "Field.h"

namespace pnx {
class GeometricalField : public QObject
{
    Q_OBJECT
public:
    explicit GeometricalField(QObject *parent);

private:

    QMap<QString, pnx::Field*> fields_;

};
}


#endif // GEOMETRICALFIELD_H
