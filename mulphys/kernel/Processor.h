#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "Common.h"
#include "ProcessorBase.h"
#include "ProcessorInterface.h"

namespace mphs {

class Processor
{
public:
    static mphs::ProcessorBase* get(const QString& processor_name, QObject* parent);
};

}


#endif // PROCESSOR_H
