#include "Operations/Operation_Group.h"

#ifdef OPERATION_GROUP_H

namespace OperationArchitecture
{
    inline uint8_t totalReturnVariables(IOperationBase * const * const &operations, const uint16_t & numberOfOperations)
    {
        uint8_t numberOfReturnVariables = 0;
        for(uint16_t i = 0; i < numberOfOperations; i++)
        {
            numberOfReturnVariables += operations[i]->NumberOfReturnVariables;
        }
        return numberOfReturnVariables;
    }
    inline uint8_t totalParameters(IOperationBase * const * const &operations, const uint16_t &numberOfOperations)
    {
        uint8_t numberOfParameters = 0;
        for(uint16_t i = 0; i < numberOfOperations; i++)
        {
            if(operations[i]->NumberOfParameters > numberOfParameters)
                numberOfParameters = operations[i]->NumberOfParameters;
        }
        return numberOfParameters;
    }

    Operation_Group::Operation_Group(IOperationBase * const * const operations, const uint16_t &numberOfOperations) :
        IOperationBase(totalReturnVariables(operations, numberOfOperations), totalParameters(operations, numberOfOperations)),
        _operations(operations),
        _numberOfOperations(numberOfOperations)
    { }

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

            _operations[i]->AbstractExecute(operationVariables);
        }
        delete operationVariables;
    }
}

#endif