#include "Operations/IOperationBase.h"
#include "Operations/OperationFactory.h"
#include "GeneratorMap.h"

#ifndef OPERATION_PACKAGE_H
#define OPERATION_PACKAGE_H
namespace OperationArchitecture
{    
    class Operation_Package : public IOperationBase
    {
    protected:
        IOperationBase *_operation;
        Variable **_executionvariables;
        uint8_t *_variableInMap;
    public:
        Operation_Package(IOperationBase *operation, Variable **executionvariables);
        ~Operation_Package();

        void AbstractExecute(Variable **variables) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut, OperationFactory *factory, GeneratorMap<Variable> *variableMap);
    };
}
#endif