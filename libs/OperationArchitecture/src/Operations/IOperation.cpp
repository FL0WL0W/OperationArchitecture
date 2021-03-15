#include "Operations/IOperation.h"

#ifdef IOPERATION_H

namespace OperationArchitecture
{
    
    Operation_Package::Operation_Package(IOperationBase *operation, OperationOrVariable *parameters)
    {
        _operation = operation;
        _parameters = parameters;
        NumberOfParameters = 0;
        ReturnsVariable = _operation->ReturnsVariable;
    }

    void Operation_Package::AbstractExecute(Variable &ret, Variable *params)
    {
        params = new Variable[_operation->NumberOfParameters];
        for(int i = 0; i < _operation->NumberOfParameters; i++)
        {
            _parameters[i].GetValue(params[i]);
        }

        _operation->AbstractExecute(ret, params);

        delete params;
    }
}

#endif