#ifndef PROCESSORBASE_H
#define PROCESSORBASE_H

#include "Common.h"
#include "ComponentBase.h"
#include "GeometricalField.h"

namespace mphs {

class ProcessorBase : public ComponentBase
{
    Q_OBJECT
public:
    explicit ProcessorBase(const QString& module_name, QObject* parent);

    virtual void init(const QJsonObject& init_config) = 0;

    ///
    /// \brief preprocess
    /// initialize gfs and use config to modify the initial values
    ///
    /// \param config
    /// \param gfs
    /// \param sectionIndices
    ///
    virtual void preprocess(QJsonObject config,
                            QMap<QString, mphs::GeometricalField*> gfs,
                            SectionIndices sectionIndices = SectionIndices()) = 0;

    virtual void process(QMap<QString, mphs::GeometricalField*> gfs,
                         SectionIndices sectionIndices = SectionIndices()) = 0;

private:

    QMap<FieldKey, FieldTraits*> field_traits_map_;
};

}



#endif // PROCESSORBASE_H
