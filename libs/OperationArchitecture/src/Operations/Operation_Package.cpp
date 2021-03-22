#include "Operations/Operation_Package.h"

#ifdef OPERATION_PACKAGE_H

namespace OperationArchitecture
{
    Operation_Package::Operation_Package(IOperationBase *operation, OperationOrVariable *parameters)
    {
        _operation = operation;
        _parameters = parameters;
        NumberOfReturnVariables = _operation->NumberOfReturnVariables;
        NumberOfParameters = 0;
    }

    void Operation_Package::AbstractExecute(Variable **variablesIn)
    {
        Variable **variables = new Variable*[_operation->NumberOfParameters + _operation->NumberOfReturnVariables];
        for(int i = 0; i < _operation->NumberOfReturnVariables; i++)
        {
            variables[i] = variablesIn[i];
        }
        Variable *params = new Variable[_operation->NumberOfParameters];
        for(int i = 0; i < _operation->NumberOfParameters; i++)
        {
            _parameters[i].GetValue(params[i]);
            variables[i + _operation->NumberOfReturnVariables] = &params[i];
        }


        _operation->AbstractExecute(variables);

        delete params;
        delete variables;
    }
}

#endif