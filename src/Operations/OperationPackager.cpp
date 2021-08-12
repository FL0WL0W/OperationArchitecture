#include "Operations/OperationPackager.h"
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

    Operation *OperationPackager::Package(const void *config, size_t &sizeOut)
    {
        const PackageOptions options = Config::CastAndOffset<PackageOptions>(config, sizeOut);

        //Create operation
        Operation *operation;
        if(options.Group)
        {
            const uint16_t numberOfOperations = Config::CastAndOffset<uint16_t>(config, sizeOut);
            Operation **operations = new Operation*[numberOfOperations];

            uint8_t numberOfReturnVariables = 0;
            uint8_t numberOfParameters = 0;

            for(int i = 0; i < numberOfOperations; i++)
            {
                size_t size = 0;
                operations[i] = Package(config, size);
                Config::OffsetConfig(config, sizeOut, size);

                numberOfReturnVariables = operations[i]->NumberOfReturnVariables;
                if(operations[i]->NumberOfParameters > numberOfParameters)
                    numberOfParameters = operations[i]->NumberOfParameters;
            }

            operation = new Operation([operations, numberOfOperations, numberOfReturnVariables, numberOfParameters](Variable **variables) 
            {
                uint32_t returnVariableLocation = 0;
                Variable** operationVariables = new Variable*[numberOfReturnVariables + numberOfParameters];
                for(int i = 0; i < numberOfOperations; i++)
                {
                    //copy return variables
                    std::memcpy(operationVariables, variables + returnVariableLocation, sizeof(Variable *) * operations[i]->NumberOfReturnVariables);
                    returnVariableLocation += operations[i]->NumberOfReturnVariables;

                    //copy parameters
                    std::memcpy(operationVariables + operations[i]->NumberOfReturnVariables, variables + numberOfReturnVariables, sizeof(Variable *) * operations[i]->NumberOfParameters);

                    operations[i]->Execute(operationVariables);
                }
                delete operationVariables;
            }, numberOfReturnVariables, numberOfParameters);
            operation->Destructor = [operations]()
            {
                delete operations;
            };
        }
    	else if(!options.OperationImmediate)
    	{
            const uint32_t operationId = Config::CastAndOffset<uint32_t>(config, sizeOut);
            std::map<uint32_t, Operation*>::iterator it = _systemBus->Operations.find(operationId);
            if (it == _systemBus->Operations.end())
            {
                //this is bad, do something 
            }
            operation = it->second;
        }
        else
        {
            size_t size = 0;
            operation = _factory->Create(config, size);
            Config::OffsetConfig(config, sizeOut, size);
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
        
        //package
        if(!(options.DoNotPackage || operation->NumberOfParameters == 0))
        {
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
            if(numberOfSubOperations > 0)
            {
                Operation **subOperations = new Operation*[numberOfSubOperations];
                for(int i = 0; i < numberOfSubOperations; i++)
                {
                    size_t size = 0;
                    subOperations[i] = Package(config, size);
                    Config::OffsetConfig(config, sizeOut, size);
                }
                //Create Package
                Operation_Package *operation_Package = new Operation_Package(operation, subOperations, parameters);
                operation = new Operation([operation_Package](Variable **variables) { operation_Package->Execute(variables); }, 1, 0);
                operation->Destructor = [operation_Package]() { delete operation_Package; };
            }
            else
            {
                //Create Package
                Operation_Package *operation_Package = new Operation_Package(operation, 0, parameters);
                operation = new Operation([operation_Package](Variable **variables) { operation_Package->Execute(variables); }, 1, 0);
                operation->Destructor = [operation_Package]() { delete operation_Package; };
            }

            delete parameters;
        }

        //wrap package in Operation_StoreVariables if storing variables or not returning variables
        if(!options.ReturnVariables && operation->NumberOfReturnVariables > 0)
        {
            Operation *subOp = operation;
            if(storageVariables == 0)
            {
                storageVariables = new Variable*[operation->NumberOfReturnVariables];
                for(int i = 0; i < operation->NumberOfReturnVariables; i++)
                {
                    const uint32_t variableId = Config::CastAndOffset<uint32_t>(config, sizeOut);
                    storageVariables[i] = _systemBus->GetOrCreateVariable(variableId);
                }
            }
            operation = new Operation([subOp, storageVariables](Variable **variables) 
            { 
                std::memcpy(storageVariables + subOp->NumberOfReturnVariables, variables, sizeof(Variable *) * subOp->NumberOfParameters);
                subOp->Execute(storageVariables);
            }, subOp->NumberOfReturnVariables, subOp->NumberOfParameters);
            operation->Destructor = [subOp]() { delete subOp; };
        }
        else if(storageVariables != 0)
        {
            Operation *subOp = operation;
            operation = new Operation([subOp, storageVariables](Variable **variables) 
            { 
                subOp->Execute(variables);
                for(int i = 0; i < subOp->NumberOfReturnVariables; i++)
                {
                    storageVariables[i]->Set(*variables[i]);
                }
            }, subOp->NumberOfReturnVariables, subOp->NumberOfParameters);
            operation->Destructor = [subOp]() { delete subOp; };
        }

        return operation;
    }
}

#endif