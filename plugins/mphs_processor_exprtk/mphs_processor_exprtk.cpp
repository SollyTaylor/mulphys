#include "mphs_processor_exprtk.h"


mphs::mphs_processor_exprtk::mphs_processor_exprtk(QObject *parent)
    : mphs::ProcessorBase (mphs::MPHS_PROCESSOR_EXPRTK_MODULE_NAME, parent)
{

}

mphs::ProcessorBase *mphs::mphs_processor_exprtk::create_plugin(QObject *parent)
{
    mphs_processor_exprtk* p = new mphs::mphs_processor_exprtk(parent);
    p->init(config_default_obj());
    return p;
}

void mphs::mphs_processor_exprtk::init(const QJsonObject &init_config)
{

}

void mphs::mphs_processor_exprtk::preprocess(QJsonObject config,
                                             QMap<QString, mphs::GeometricalField *> gfs,
                                             SectionIndices sectionIndices)
{

}

void mphs::mphs_processor_exprtk::process(QMap<QString, mphs::GeometricalField *> gfs,
                                          SectionIndices sectionIndices)
{

}

