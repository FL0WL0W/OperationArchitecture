#include "Operations/IOperationBase.h"
#include <utility>

#ifndef OPERATION_PACKAGE_H
#define OPERATION_PACKAGE_H
namespace OperationArchitecture
{
    struct OperationOrVariable
    {
        Variable *VariableLocation;
        uint8_t OperationId;
        uint8_t OperationReturnVariableId;
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

    class Operation_Package : public IOperationBase
    {
        protected:
        IOperationBase *_operation;
        IOperationBase **_subOperations;
        uint8_t _numberOfSubOperations;
        Variable ***_operationVariables;
        Variable **_variables;
        public:
        Operation_Package(IOperationBase *operation, IOperationBase **subOperations, OperationOrVariable *parameters);
        ~Operation_Package();
        void AbstractExecute(Variable **variables) override;
    };
}
#endif