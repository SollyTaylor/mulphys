#ifndef MPHS_READER_STL_H
#define MPHS_READER_STL_H

#include "Common.h"
#include "GeometricalField.h"

#include "ProcessorBase.h"
#include "ProcessorInterface.h"
#include "ComponentBase.h"
#include "exprtk.hpp"

namespace mphs {

const QString MPHS_PROCESSOR_EXPRTK_MODULE_NAME = "mphs_processor_exprtk";

class mphs_processor_exprtk :
        public mphs::ProcessorBase,
        public mphs::ProcessorInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QGenericPluginFactoryInterface" FILE "mphs_processor_exprtk.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(mphs::ProcessorInterface)
public:
    mphs_processor_exprtk(QObject* parent = nullptr);
    virtual ~mphs_processor_exprtk(){}

    mphs::ProcessorBase* create_plugin(QObject* parent);

    virtual void init(const QJsonObject& init_config);
    virtual void preprocess(QJsonObject config,
                            QMap<QString, mphs::GeometricalField*> gfs,
                            SectionIndices sectionIndices = SectionIndices());

    virtual void process(QMap<QString, mphs::GeometricalField*> gfs,
                         SectionIndices sectionIndices = SectionIndices());

};

}

#endif // MPHS_READER_STL_H
