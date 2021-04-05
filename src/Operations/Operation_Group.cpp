#include "Operations/Operation_Group.h"

#ifdef OPERATION_GROUP_H

namespace OperationArchitecture
{
    Operation_Group::Operation_Group(IOperationBase **operations, uint16_t numberOfOperations)
    {
        _operations = operations;
        _numberOfOperations = numberOfOperations;

		NumberOfReturnVariables = 0;
        for(int i = 0; i < _numberOfOperations; i++)
        {
            NumberOfReturnVariables += _operations[i]->NumberOfReturnVariables;
            if(_operations[i]->NumberOfParameters > NumberOfParameters)
                NumberOfParameters = _operations[i]->NumberOfParameters;
        }
    }

    void Operation_Group::AbstractExecute(Variable **variables)
    {
        uint32_t returnVariableLocation = 0;
        Variable** operationVariables = new Variable*[NumberOfReturnVariables + NumberOfParameters];
        for(int i = 0; i < _numberOfOperations; i++)
        {
            //copy return variables
            std::memcpy(operationVariables, variables + returnVariableLocation, sizeof(Variable *) * _operations[i]->NumberOfReturnVariables);
            returnVariableLocation += _operations[i]->NumberOfReturnVariables;

            //copy parameters
            std::memcpy(operationVariables + _operations[i]->NumberOfReturnVariables, variables + NumberOfReturnVariables, sizeof(Variable *) * _operations[i]->NumberOfParameters);

            _operations[i]->AbstractExecute(variables);
        }
        delete operationVariables;
    }
}

#endif