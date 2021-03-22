#include "Operations/Operation_Package.h"

#ifdef OPERATION_PACKAGE_H

namespace OperationArchitecture
{
    Operation_Package::Operation_Package(IOperationBase *operation, IOperationBase **subOperations, OperationOrVariable *parameters)
    {
        _operation = operation;
        _subOperations = subOperations;
        _parameters = parameters;
        _numberOfSubOperations = 0;
        for(int i = 0; i < _operation->NumberOfParameters; i++)
        {
            if(parameters[i].OperationId > _numberOfSubOperations)
                _numberOfSubOperations = parameters[i].OperationId;
        }

        NumberOfReturnVariables = _operation->NumberOfReturnVariables;
        NumberOfParameters = 0;
    }

    void Operation_Package::AbstractExecute(Variable **variablesIn)
    {
        Variable ***operationVariables = new Variable**[_numberOfSubOperations];
        for(int i = 0; i < _numberOfSubOperations; i++)
        {
            operationVariables[i] = new Variable*[_subOperations[i]->NumberOfReturnVariables];
            for(int q = 0; q < _subOperations[i]->NumberOfReturnVariables; q++)
            {
                operationVariables[i][q] = new Variable();
            }
            _subOperations[i]->AbstractExecute(operationVariables[i]);
        }

        Variable **variables = new Variable*[_operation->NumberOfParameters + _operation->NumberOfReturnVariables];
        for(int i = 0; i < _operation->NumberOfReturnVariables; i++)
        {
            variables[i] = variablesIn[i];
        }
        for(int i = 0; i < _operation->NumberOfParameters; i++)
        {
            if(_parameters[i].OperationId > 0)
            {
                variables[i + _operation->NumberOfReturnVariables] = operationVariables[_parameters[i].OperationId-1][_parameters[i].OperationReturnVariableId];
            }
            else
            {
                variables[i + _operation->NumberOfReturnVariables] = _parameters[i].VariableLocation;
            }
        }

        _operation->AbstractExecute(variables);

        for(int i = 0; i < _numberOfSubOperations; i++)
        {
            for(int q = 0; q < _subOperations[i]->NumberOfReturnVariables; q++)
            {
                delete operationVariables[i][q];
            }
            delete operationVariables[i];
        }
        delete operationVariables;
        delete variables;
    }
}

#endif