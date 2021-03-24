#include "Operations/Operation_Execute.h"

#ifdef OPERATION_EXECUTE_H

namespace OperationArchitecture
{
    Operation_Execute::Operation_Execute(IOperationBase *operation)
    {
        _operation = operation;
        _variables = new Variable*[_operation->NumberOfParameters + _operation->NumberOfReturnVariables];
        for(int i = 0; i < _operation->NumberOfReturnVariables; i++)
        {
            _variables[i] = new Variable();
        }
        NumberOfReturnVariables = 0;
        NumberOfParameters = _operation->NumberOfParameters;
    }

    Operation_Execute::~Operation_Execute()
    {
        delete _variables;
    }

    void Operation_Execute::AbstractExecute(Variable **variables)
    {
        for(int i = 0; i < _operation->NumberOfParameters; i++)
        {
            _variables[i+_operation->NumberOfReturnVariables] = variables[i];
        }
        _operation->AbstractExecute(_variables);
    }
}

#endif