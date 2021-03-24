#include "Operations/Operation_StoreVariables.h"

#ifdef OPERATION_STOREVARIABLES_H

namespace OperationArchitecture
{
    Operation_StoreVariables::Operation_StoreVariables(IOperationBase *operation, Variable **variables, bool returnVariables)
    {
        _operation = operation;
        NumberOfReturnVariables = _operation->NumberOfReturnVariables;
        NumberOfParameters = _operation->NumberOfParameters;

        _returnVariables = returnVariables;
        _variables = new Variable*[NumberOfReturnVariables + _returnVariables? 0 : NumberOfParameters];
        std::memcpy(_variables, variables, sizeof(Variable *) * NumberOfReturnVariables);
    }

    Operation_StoreVariables::~Operation_StoreVariables()
    {
        delete _variables;
    }

    void Operation_StoreVariables::AbstractExecute(Variable **variables)
    {
        if(_returnVariables)
        {
            _operation->AbstractExecute(variables);
            for(int i = 0; i < NumberOfReturnVariables; i++)
            {
               _variables[i]->Set(*variables[i]);
            }
        }
        else
        {
            std::memcpy(_variables + NumberOfReturnVariables, variables, sizeof(Variable *) * NumberOfParameters);
            _operation->AbstractExecute(_variables);
        }
    }
}

#endif