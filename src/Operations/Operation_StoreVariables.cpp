#include "Operations/Operation_StoreVariables.h"

#ifdef OPERATION_STOREVARIABLES_H

namespace OperationArchitecture
{
    Operation_StoreVariables::Operation_StoreVariables(Variable **variables, IOperationBase *operation)
    {
        _variables = variables;
        _operation = operation;
        NumberOfReturnVariables = _operation->NumberOfReturnVariables;
        NumberOfParameters = _operation->NumberOfParameters;
    }

    void Operation_StoreVariables::AbstractExecute(Variable **variables)
    {
        _operation->AbstractExecute(variables);
        for(int i = 0; i < NumberOfReturnVariables; i++)
        {
            _variables[i]->Set(*variables[i]);
        }
    }
}

#endif