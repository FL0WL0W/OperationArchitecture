#include "Operations/Operation_StoreVariables.h"

#ifdef OPERATION_STOREVARIABLES_H

namespace OperationArchitecture
{
    Operation_StoreVariables::Operation_StoreVariables(IOperationBase *operation, Variable **variables, bool returnVariables)
    {
        _operation = operation;
        _returnVariables = returnVariables;
        NumberOfReturnVariables = _returnVariables? _operation->NumberOfReturnVariables : 0;
        NumberOfParameters = _operation->NumberOfParameters;

        _variables = new Variable*[_operation->NumberOfParameters + _operation->NumberOfReturnVariables];
        if(variables == 0)
        {
            for(int i = 0; i < _operation->NumberOfReturnVariables; i++)
            {
                _variables[i] = new Variable();
            }
        }
        else
        {
            std::memcpy(_variables, variables, sizeof(Variable *) * _operation->NumberOfReturnVariables);
        }
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
            for(int i = 0; i < _operation->NumberOfReturnVariables; i++)
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