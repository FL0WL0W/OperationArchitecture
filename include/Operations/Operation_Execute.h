#include "Operations/IOperationBase.h"
#include <utility>

#ifndef OPERATION_EXECUTE_H
#define OPERATION_EXECUTE_H
namespace OperationArchitecture
{
    struct OperationOrVariable
    {
        uint8_t OperationId;
        uint8_t OperationReturnVariableId;
        Variable *VariableLocation;
        OperationOrVariable()
        {
            OperationId = 0;
            OperationReturnVariableId = 0;
            VariableLocation = 0;
        }
        OperationOrVariable(Variable *variable)
        {
            OperationId = 0;
            OperationReturnVariableId = 0;
            VariableLocation = variable;
        }
        OperationOrVariable(uint8_t operationId, uint8_t operationReturnVariableID)
        {
            OperationId = operationId;
            OperationReturnVariableId = operationReturnVariableID;
            VariableLocation = 0;
        }
    };

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