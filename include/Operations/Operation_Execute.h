#include "Operations/IOperationBase.h"
#include <utility>

#ifndef OPERATION_EXECUTE_H
#define OPERATION_EXECUTE_H
namespace OperationArchitecture
{
    class Operation_Execute : public IOperationBase
    {
        protected:
        IOperationBase *_operation;
        Variable **_variables;
        public:
        Operation_Execute(IOperationBase *operation);
        ~Operation_Execute();
        void AbstractExecute(Variable **variables) override;
    };
}
#endif