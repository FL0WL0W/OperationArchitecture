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
        bool _returnVariables;
        
        public:
        Operation_StoreVariables(IOperationBase *operation, Variable **variables, bool returnVariables);
        ~Operation_StoreVariables();

        void AbstractExecute(Variable **variables) override;
    };
}
#endif