#include "Config.h"
#include "Operations/Operation_Package.h"

#ifdef OPERATION_PACKAGE_H

namespace OperationArchitecture
{    
    static inline uint8_t numberOfInputs(Variable **executionvariables, uint8_t numberOfVariables)
    {
        uint8_t v = 0;
        for(uint8_t i = 0; i < numberOfVariables; i++)
        {
            if(executionvariables[i] == 0)
            {
                v++;
            }
        }
        return v;
    }

    static inline uint8_t * variableInMap(Variable **executionvariables, uint8_t numberOfVariables)
    {
        uint8_t *map = new uint8_t[numberOfInputs(executionvariables, numberOfVariables)];
        uint8_t v = 0;
        for(uint8_t i = 0; i < numberOfVariables; i++)
        {
            if(executionvariables[i] == 0)
            {
                map[v] = i;
                v++;
            }
        }
        return map;
    }

    //operation will not be deleted when package is deleted
    //executionvariables array will be deleted when package is deleted. contents of executionvariables will not be deleted
    Operation_Package::Operation_Package(AbstractOperation *operation, Variable **executionvariables, uint8_t numberOfVariables) :
        _operation(operation),
        _executionvariables(executionvariables),
        _variableInMap(variableInMap(executionvariables, numberOfVariables)),
        _numberOfVariables(numberOfVariables),
        _numberOfInputs(numberOfInputs(executionvariables, numberOfVariables))
    { }

    Operation_Package::~Operation_Package()
    {
        delete[] _executionvariables;
        delete[] _variableInMap;
    }

    void Operation_Package::AbstractExecute(Variable **variablesIn)
    {
        for(uint8_t i = 0; i < _numberOfInputs; i++)
        {
            _executionvariables[_variableInMap[i]] = variablesIn[i];
        }
        _operation->AbstractExecute(_executionvariables);
    }

    AbstractOperation *Operation_Package::Create(const void *config, size_t &sizeOut, OperationFactory *factory, GeneratorMap<Variable> *variableMap)
    {
        //Create operation
        size_t size = 0;
        AbstractOperation *operation = factory->Create(config, size);
        Config::OffsetConfig(config, sizeOut, size);
        const uint8_t numberOfVariables = Config::CastAndOffset<uint8_t>(config, sizeOut);

        //check to make sure operation is valid
        if(operation == 0)
            return 0;

        //Create Execute Variables
        Variable **executeVariables = new Variable*[numberOfVariables];
        for(int i = 0; i < numberOfVariables; i++)
        {
            const uint32_t variableId = Config::CastAndOffset<uint32_t>(config, sizeOut);
            executeVariables[i] = variableId == 0? 0 : variableMap->GenerateValue(variableId);
        }

        return new Operation_Package(operation, executeVariables, numberOfVariables);
    }
}

#endif