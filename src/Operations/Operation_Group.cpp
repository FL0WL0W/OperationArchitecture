#include "Config.h"
#include "Operations/Operation_Group.h"

#ifdef OPERATION_GROUP_H

namespace OperationArchitecture
{
    inline uint8_t totalReturnVariables(AbstractOperation * const * const &operations, const uint16_t & numberOfOperations)
    {
        uint8_t numberOfReturnVariables = 0;
        for(uint16_t i = 0; i < numberOfOperations; i++)
        {
            if(operations[i] != 0)
                numberOfReturnVariables += operations[i]->NumberOfReturnVariables;
        }
        return numberOfReturnVariables;
    }
    inline uint8_t totalParameters(AbstractOperation * const * const &operations, const uint16_t &numberOfOperations)
    {
        uint8_t numberOfParameters = 0;
        for(uint16_t i = 0; i < numberOfOperations; i++)
        {
            if(operations[i] != 0 && operations[i]->NumberOfParameters > numberOfParameters)
                numberOfParameters = operations[i]->NumberOfParameters;
        }
        return numberOfParameters;
    }

    //operations array will be deleted when package is deleted, contents of operations array will not be deleted
    Operation_Group::Operation_Group(AbstractOperation * const * const operations, const uint16_t &numberOfOperations) :
        AbstractOperation(totalReturnVariables(operations, numberOfOperations), totalParameters(operations, numberOfOperations)),
        _operations(operations),
        _numberOfOperations(numberOfOperations)
    { }

    Operation_Group::~Operation_Group()
    {
        delete _operations;
    }

    void Operation_Group::AbstractExecute(Variable **variables)
    {
        uint32_t returnVariableLocation = 0;
        Variable** operationVariables = new Variable*[NumberOfReturnVariables + NumberOfParameters];
        for(uint16_t i = 0; i < _numberOfOperations; i++)
        {
            if(_operations[i] == 0)
                continue;
                
            //copy return variables
            std::memcpy(operationVariables, variables + returnVariableLocation, sizeof(Variable *) * _operations[i]->NumberOfReturnVariables);
            returnVariableLocation += _operations[i]->NumberOfReturnVariables;

            //copy parameters
            std::memcpy(operationVariables + _operations[i]->NumberOfReturnVariables, variables + NumberOfReturnVariables, sizeof(Variable *) * _operations[i]->NumberOfParameters);

            _operations[i]->AbstractExecute(operationVariables);
        }
        delete operationVariables;
    }
    
    AbstractOperation *Operation_Group::Create(const void *config, size_t &sizeOut, OperationFactory *factory)
    {
        const uint16_t numberOfOperations = Config::CastAndOffset<uint16_t>(config, sizeOut);
        AbstractOperation **operations = new AbstractOperation*[numberOfOperations];

        for(uint16_t i = 0; i < numberOfOperations; i++)
        {
            size_t size = 0;
            operations[i] = factory->Create(config, size);
            Config::OffsetConfig(config, sizeOut, size);
        }

        return new Operation_Group(operations, numberOfOperations);
    }
}

#endif