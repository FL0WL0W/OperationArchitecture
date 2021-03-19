#include "Operations/Operation_StoreVariable.h"

#ifdef OPERATION_STOREVARIABLE_H

namespace OperationArchitecture
{
    Operation_StoreVariable::Operation_StoreVariable(Variable *variable, IOperationBase *operation)
    {
        NumberOfParameters = 0;
        ReturnsVariable = true;
        _variable = variable;
        _operation = operation;
    }

    void Operation_StoreVariable::AbstractExecute(Variable &ret, Variable *params)
    {
        _operation->AbstractExecute(*_variable, params);
        
        ret = *_variable;
    }
}

#endif