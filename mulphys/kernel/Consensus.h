#ifndef FIELDTRAITS_H
#define FIELDTRAITS_H

#include "Common.h"
#include "Configurator.h"

namespace mphs {

class Consensus : public QObject
{
    Q_OBJECT
public:
    explicit Consensus(QObject *parent = nullptr);
    virtual ~Consensus(){}

    void init(Configurator config);

private:

    // field properties
    QString name_;
    QString description_;

    // where the physical data located
    FieldLocation location_;

    // field data type
    FieldDataType data_type_;

    FieldIOType io_type_;

};

}



#endif // FIELDTRAITS_H
