#include "Operations/IOperationBase.h"

#ifndef OPERATION_STOREVARIABLES_H
#define OPERATION_STOREVARIABLES_H
namespace OperationArchitecture
{
    class Operation_StoreVariables : public IOperationBase
    {
        protected:
        Variable **_variables;
        IOperationBase *_operation;
        
        public:
        void AbstractExecute(Variable **variables) override;

        Operation_StoreVariables(Variable **variables, IOperationBase *operation);
    };
}
#endif