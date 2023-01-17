#include "Config.h"
#include "Operations/Operation_Package.h"

#ifdef OPERATION_PACKAGE_H

namespace OperationArchitecture
{    
    inline uint8_t totalReturnVariables(AbstractOperation *operation, Variable **executionvariables)
    {
        uint8_t numberOfReturnVariables = 0;
        for(uint8_t i = 0; i < operation->NumberOfReturnVariables; i++)
        {
            if(executionvariables[i] == 0)
                numberOfReturnVariables++;
        }
        return numberOfReturnVariables;
    }
    inline uint8_t totalParameters(AbstractOperation *operation, Variable **executionvariables)
    {
        uint8_t numberOfParameters = 0;
        for(uint8_t i = 0; i < operation->NumberOfParameters; i++)
        {
            if(executionvariables[i + operation->NumberOfReturnVariables] == 0)
                numberOfParameters++;
        }
        return numberOfParameters;
    }

    //operation will not be deleted when package is deleted
    //executionvariables array will be deleted when package is deleted. contents of executionvariables will not be deleted
    Operation_Package::Operation_Package(AbstractOperation *operation, Variable **executionvariables) :
        AbstractOperation(totalReturnVariables(operation, executionvariables), totalParameters(operation, executionvariables)),
        _operation(operation),
        _executionvariables(executionvariables)
    {
        _variableInMap = new uint8_t[NumberOfParameters + NumberOfReturnVariables];
        uint8_t v = 0;
        for(uint8_t i = 0; i < operation->NumberOfParameters + operation->NumberOfReturnVariables; i++)
        {
            if(executionvariables[i] == 0)
            {
                _variableInMap[v] = i;
                v++;
            }
        }
    }

    Operation_Package::~Operation_Package()
    {
        delete _executionvariables;
        delete[] _variableInMap;
    }

    void Operation_Package::AbstractExecute(Variable **variablesIn)
    {
        for(uint8_t i = 0; i < NumberOfParameters +NumberOfReturnVariables; i++)
        {
            _executionvariables[_variableInMap[i]] = variablesIn[i];
        }
        _operation->AbstractExecute(_executionvariables);
    }

    AbstractOperation *Operation_Package::Create(const void *config, size_t &sizeOut, OperationFactory *factory, GeneratorMap<Variable> *variableMap)
    {
        const uint32_t factoryId = Config::Cast<uint32_t>(config);

        //Create operation
        size_t size = 0;
        AbstractOperation *operation = factory->Create(config, size);
        Config::OffsetConfig(config, sizeOut, size);

        //Create Execute Variables
        Variable **executeVariables = new Variable*[operation->NumberOfReturnVariables + operation->NumberOfParameters];
        for(int i = 0; i < operation->NumberOfReturnVariables + operation->NumberOfParameters; i++)
        {
            const uint32_t variableId = Config::CastAndOffset<uint32_t>(config, sizeOut);
            executeVariables[i] = variableId == 0? 0 : variableMap->GenerateValue(variableId);
        }

        return new Operation_Package(operation, executeVariables);
    }
}

#endif