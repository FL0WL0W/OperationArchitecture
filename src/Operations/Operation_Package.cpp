#include "Operations/Operation_Package.h"

#ifdef OPERATION_PACKAGE_H

namespace OperationArchitecture
{
    //subOperations will be deleted when package is deleted
    Operation_Package::Operation_Package(IOperationBase *operation, IOperationBase **subOperations, OperationOrVariable *parameters) :
        IOperationBase(operation->NumberOfReturnVariables, 0)
    {
        _operation = operation;
        _numberOfSubOperations = 0;
        _subOperations = subOperations;
        for(int i = 0; i < _operation->NumberOfParameters; i++)
        {
            if(parameters[i].OperationId > _numberOfSubOperations)
                _numberOfSubOperations = parameters[i].OperationId;
        }
        if(_numberOfSubOperations > 0)
        {
            _operationVariables = new Variable**[_numberOfSubOperations];
            for(int i = 0; i < _numberOfSubOperations; i++)
            {
                _operationVariables[i] = new Variable*[_subOperations[i]->NumberOfReturnVariables];
                for(int q = 0; q < _subOperations[i]->NumberOfReturnVariables; q++)
                {
                    _operationVariables[i][q] = new Variable();
                }
            }
        }
        _variables = new Variable*[_operation->NumberOfParameters + _operation->NumberOfReturnVariables];
        for(int i = 0; i < _operation->NumberOfParameters; i++)
        {
            if(parameters[i].OperationId > 0)
            {
                _variables[i + _operation->NumberOfReturnVariables] = _operationVariables[parameters[i].OperationId-1][parameters[i].OperationReturnVariableId];
            }
            else
            {
                _variables[i + _operation->NumberOfReturnVariables] = parameters[i].VariableLocation;
            }
        }
    }

    Operation_Package::~Operation_Package()
    {
        for(int i = 0; i < _numberOfSubOperations; i++)
        {
            for(int q = 0; q < _subOperations[i]->NumberOfReturnVariables; q++)
            {
                delete _operationVariables[i][q];
            }
            delete _operationVariables[i];
        }
        delete _operationVariables;
        delete _variables;
        delete _subOperations;
    }

    void Operation_Package::AbstractExecute(Variable **variablesIn)
    {
        for(int i = 0; i < _numberOfSubOperations; i++)
        {
            _subOperations[i]->AbstractExecute(_operationVariables[i]);
        }

        for(int i = 0; i < _operation->NumberOfReturnVariables; i++)
        {
            _variables[i] = variablesIn[i];
        }

        _operation->AbstractExecute(_variables);
    }
}

#endif