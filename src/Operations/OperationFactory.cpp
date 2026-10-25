#include "Operations/OperationFactory.h"
#include "Config.h"
#include <algorithm>

#ifdef OPERATIONFACTORY_H

namespace OperationArchitecture
{
	void OperationFactory::Delete()
	{
		_staticOperations.clear();
		for (std::list<AbstractOperation*>::iterator it = _dynamicOperations.begin(); it != _dynamicOperations.end(); ++it){
			delete *it;
		}
		_dynamicOperations.clear();
		_factories = 0;
		_numberOfFactories = 0;
	}

    void OperationFactory::Register(const OperationFactoryEntry *factories, size_t numberOfFactories)
    {
        _factories = factories;
        _numberOfFactories = numberOfFactories;
    }

    void OperationFactory::Register(const uint32_t id, AbstractOperation* operation)
    {
		Unregister(id);
		_staticOperations.insert(std::pair<uint32_t, AbstractOperation*>(id, operation));
    }

	void OperationFactory::Unregister(const uint32_t id)
	{
		const std::map<uint32_t, AbstractOperation*>::iterator itOp = _staticOperations.find(id);
		if (itOp != _staticOperations.end())
			_staticOperations.erase(itOp);
	}
    
    AbstractOperation *OperationFactory::Create(const void *config, size_t &sizeOut)
    {
        if (!config) return nullptr;

        const uint32_t factoryId = Config::CastAndOffset<uint32_t>(config, sizeOut);

		//these are all static instance operations
		const std::map<uint32_t, AbstractOperation*>::iterator itOp = _staticOperations.find(factoryId);
		if (itOp != _staticOperations.end())
            return itOp->second;

        // Perform a binary search on the sorted entries array
        auto it = std::lower_bound(_factories, _factories + _numberOfFactories, factoryId, 
            [](const OperationFactoryEntry& entry, uint32_t id) {
                return entry.ID < id;
            });

        if (it != _factories + _numberOfFactories && it->ID == factoryId)
        {
			AbstractOperation *operation = it->Create(config, sizeOut);
			_dynamicOperations.push_front(operation);
			return operation;
        }

        return nullptr;
    }
}

#endif