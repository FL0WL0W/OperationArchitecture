#include "Config.h"
#include "Operations/Operation_ConditionExecute.h"

namespace OperationArchitecture
{
    Operation_ConditionExecute::Operation_ConditionExecute(AbstractOperation *operation) :
        _operation(operation)
    { }

    Operation_ConditionExecute::~Operation_ConditionExecute()
    {
        delete _operation;
    }

    void Operation_ConditionExecute::AbstractExecute(Variable **variables)
    {
        if(_operation != nullptr && variables != nullptr && variables[0] != nullptr && static_cast<bool>(*variables[0]))
        {
            _operation->AbstractExecute(variables + 1);
        }
    }

    AbstractOperation *Operation_ConditionExecute::Create(const void *config, size_t &sizeOut, OperationFactory *factory)
    {
        size_t size = 0;
        AbstractOperation *operation = factory->Create(config, size);
        Config::OffsetConfig(config, sizeOut, size);
        if(operation == nullptr)
            return nullptr;

        return new Operation_ConditionExecute(operation);
    }
}
