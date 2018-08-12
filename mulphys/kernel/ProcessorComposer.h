#ifndef PROCESSORCOMPOSER_H
#define PROCESSORCOMPOSER_H

#include "Common.h"
#include "IntegratorBase.h"
#include "ProcessorBase.h"

namespace mphs {

///
/// \brief The ProcessorComposer class
///
/// encapsulate the processing line into a function
///
class ProcessorComposer : public QObject
{
    Q_OBJECT
public:
    explicit ProcessorComposer(QObject* parent);

    void init(QJsonObject config);

private:

    QMap<QString, mphs::GeometricalField*> gfs_;
    SectionIndices sectionIndices_;

    QList<mphs::ProcessorBase*> processor_line_;

    IntegratorBase* integrator_;
};

}


#endif // PROCESSORCOMPOSER_H
