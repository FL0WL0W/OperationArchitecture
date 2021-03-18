#include "Operations/OperationPackager.h"
#include "Operations/Operation_StoreVariable.h"
#include "Config.h"
#include "Packed.h"

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
        PACK(
        struct Options 
        {
            bool OperationImmediate : 1;
            bool StoreVariable : 1;
        });

        const Options options = Config::CastAndOffset<Options>(config, sizeOut);

        Variable * variable = 0;
        if(options.StoreVariable)
        {
            const uint32_t variableId = Config::CastAndOffset<uint32_t>(config, sizeOut);
            variable = _systemBus->GetOrCreateVariable(variableId);
        }

        IOperationBase *operation;
    	if(options.OperationImmediate)
    	{
            operation = _factory->Create(config, sizeOut);
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
        IOperationBase * const package = new Operation_Package(operation, CreateParameters(operation->NumberOfParameters, config, sizeOut));

        if(variable != 0)
            return new Operation_StoreVariable(variable, package);

        return package;
    }

    OperationOrVariable *OperationPackager::CreateParameters(const uint8_t numberOfParameters, const void *config, unsigned int &sizeOut)
    {
        OperationOrVariable *parameters = new OperationOrVariable[numberOfParameters];
        for(int i = 0; i < numberOfParameters; i++)
        {
            parameters[i] = CreateParameter(config, sizeOut);
        }
        return parameters;
    }

    OperationOrVariable OperationPackager::CreateParameter(const void *config, unsigned int &sizeOut)
    {
        OperationOrVariable ov;

        const bool operation = Config::CastAndOffset<bool>(config, sizeOut);

        if(operation)
        {
            return OperationOrVariable(Package(config, sizeOut));
        }
        else
        {
            const uint32_t variableId = Config::CastAndOffset<uint32_t>(config, sizeOut);
           return OperationOrVariable(_systemBus->GetOrCreateVariable(variableId));
        }         

        return ov;
    }
}

#endif