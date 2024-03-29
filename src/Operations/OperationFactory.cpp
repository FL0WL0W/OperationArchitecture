#include "Operations/OperationFactory.h"
#include "Config.h"

#ifdef OPERATIONFACTORY_H

namespace OperationArchitecture
{    
	OperationFactory::~OperationFactory()
	{
		for (std::list<AbstractOperation*>::iterator it = _dynamicOperations.begin(); it != _dynamicOperations.end(); ++it){
			delete *it;
		}
		Clear();
	}

	void OperationFactory::Clear()
	{
		_staticOperations.clear();
		_factories.clear();
	}

    void OperationFactory::Register(const uint32_t id, std::function<AbstractOperation*(const void *, size_t &)> factory)
    {
		Unregister(id);
		_factories.insert(std::pair<uint32_t, std::function<AbstractOperation*(const void *, size_t &)>>(id, factory));
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

		const std::map<uint32_t, std::function<AbstractOperation*(const void *, size_t &)>>::iterator it = _factories.find(id);
		if (it != _factories.end())
			_factories.erase(it);
	}

    AbstractOperation *OperationFactory::Create(const void *config, size_t &sizeOut)
    {
        const uint32_t factoryId = Config::CastAndOffset<uint32_t>(config, sizeOut);

		//these are all static instance operations
		const std::map<uint32_t, AbstractOperation*>::iterator itOp = _staticOperations.find(factoryId);
		if (itOp != _staticOperations.end())
            return itOp->second;

		//these factories create a dynamic instance of the operation that needs to be tracked so it can be later deleted
		const std::map<uint32_t, std::function<AbstractOperation*(const void *, size_t &)>>::iterator it = _factories.find(factoryId);
		if (it != _factories.end())
		{
			AbstractOperation *operation = it->second(config, sizeOut);
			_dynamicOperations.push_front(operation);
			return operation;
		}

        return 0;
    }
}

#endif