#include "Operations/IOperationBase.h"

#ifndef OPERATION_STOREVARIABLE_H
#define OPERATION_STOREVARIABLE_H
namespace OperationArchitecture
{
    class Operation_StoreVariable : public IOperationBase
    {
        protected:
        Variable * _variable;
        IOperationBase *_operation;
        
        public:
        void AbstractExecute(Variable &ret, Variable *params) override;

        Operation_StoreVariable(Variable *variable, IOperationBase *operation);
    };
}
#endif