#ifndef PROCESSORINTERFACE_H
#define PROCESSORINTERFACE_H

#include "Common.h"
#include "ProcessorBase.h"

namespace mphs {

class ProcessorInterface {
public:
    virtual mphs::ProcessorBase* create_plugin(QObject* parent) = 0;
    virtual ~ProcessorInterface(){}
};
}
Q_DECLARE_INTERFACE(mphs::ProcessorInterface, "mphs.processor.interface")

#endif // PROCESSORINTERFACE_H
