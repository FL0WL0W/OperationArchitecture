#include "Config.h"
#include "Operations/Operation_Group.h"

#ifdef OPERATION_GROUP_H

namespace OperationArchitecture
{
    //operations array will be deleted when package is deleted, contents of operations array will not be deleted
    Operation_Group::Operation_Group(AbstractOperation * const * const operations, const uint16_t &numberOfOperations) :
        _operations(operations),
        _numberOfOperations(numberOfOperations)
    { }

    Operation_Group::~Operation_Group()
    {
        delete[] _operations;
    }

    void Operation_Group::AbstractExecute(Variable **variables)
    {
        for(uint16_t i = 0; i < _numberOfOperations; i++)
        {
            _operations[i]->AbstractExecute(variables);
        }
    }
    
    AbstractOperation *Operation_Group::Create(const void *config, size_t &sizeOut, OperationFactory *factory)
    {
        uint16_t numberOfOperations = Config::CastAndOffset<uint16_t>(config, sizeOut);
        AbstractOperation **operations = new AbstractOperation*[numberOfOperations];

        for(uint16_t i = 0; i < numberOfOperations; i++)
        {
            size_t size = 0;
            operations[i] = factory->Create(config, size);
            Config::OffsetConfig(config, sizeOut, size);
            //remove operation if it is invalid
            if(operations[i] == 0)
            {
                i--;
                numberOfOperations--;
            }
        }

        return new Operation_Group(operations, numberOfOperations);
    }
}

#endif