#include "Operations/OperationPackager.h"
#include "Operations/Operation_StoreVariables.h"
#include "Config.h"

#ifdef OPERATIONPACKAGER_H

namespace OperationArchitecture
{
    Variable *SystemBus::GetOrCreateVariable(uint32_t variableId)
    {
        Variable *ret;
        std::map<uint32_t, Variable*>::iterator it = Variables.find(variableId);
        if (it == Variables.end())
        {
            ret = new Variable();
            Variables.insert(std::pair<uint32_t, Variable *>(variableId, ret));
        }
        else
        {
            ret = it->second;
        }

        return ret;
    }

    OperationPackager::OperationPackager(OperationFactory *factory, SystemBus *systemBus)
    {
        _factory = factory;
        _systemBus = systemBus;
    }

    IOperationBase *OperationPackager::Package(const void *config, unsigned int &sizeOut)
    {
        const PackageOptions options = Config::CastAndOffset<PackageOptions>(config, sizeOut);

        //Create operation
        IOperationBase *operation;
    	if(options.OperationImmediate)
    	{
            unsigned int size = 0;
            operation = _factory->Create(config, size);
            Config::OffsetConfig(config, sizeOut, size);
        }
        else
        {
            const uint32_t operationId = Config::CastAndOffset<uint32_t>(config, sizeOut);
            std::map<uint32_t, IOperationBase*>::iterator it = _systemBus->Operations.find(operationId);
            if (it == _systemBus->Operations.end())
            {
                //this is bad, do something 
            }
            operation = it->second;
        }

        //Create Storage Variables
        Variable **storageVariables = 0;
        if(options.StoreVariables)
        {
            storageVariables = new Variable*[operation->NumberOfReturnVariables];
            for(int i = 0; i < operation->NumberOfReturnVariables; i++)
            {
                const uint32_t variableId = Config::CastAndOffset<uint32_t>(config, sizeOut);
                storageVariables[i] = _systemBus->GetOrCreateVariable(variableId);
            }
        }

        //Create Parameters
        uint8_t numberOfSubOperations = 0;
        OperationOrVariable *parameters = new OperationOrVariable[operation->NumberOfParameters];
        for(int i = 0; i < operation->NumberOfParameters; i++)
        {
            const uint8_t operationReturnId = Config::CastAndOffset<uint8_t>(config, sizeOut);

            if(operationReturnId > 0)
            {
                if(operationReturnId > numberOfSubOperations)
                {
                    numberOfSubOperations = operationReturnId;
                }

                const uint8_t operationReturnVariableId = Config::CastAndOffset<uint8_t>(config, sizeOut);
                parameters[i] = OperationOrVariable(operationReturnId, operationReturnVariableId);
            }
            else
            {
                const uint32_t variableId = Config::CastAndOffset<uint32_t>(config, sizeOut);
                parameters[i] = OperationOrVariable(_systemBus->GetOrCreateVariable(variableId));
            }
        }

        //Create sub operations
        IOperationBase **subOperations = new IOperationBase*[numberOfSubOperations];
        for(int i = 0; i < numberOfSubOperations; i++)
        {
            unsigned int size = 0;
            subOperations[i] = Package(config, size);
            Config::OffsetConfig(config, sizeOut, size);
        }

        //Create Package
        IOperationBase * const package = new Operation_Package(operation, subOperations, parameters);

        //wrap package in Operation_StoreVariables if storing variables
        if(storageVariables != 0)
            return new Operation_StoreVariables(storageVariables, package);

        return package;
    }
}

#endif