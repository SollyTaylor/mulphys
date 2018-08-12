#include "Processor.h"

mphs::ProcessorBase *mphs::Processor::get(const QString &processor_name, QObject *parent)
{
    return mphs::Common::get<ProcessorInterface, ProcessorBase>(processor_name, parent);
}
