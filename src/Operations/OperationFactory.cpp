#include "Operations/OperationFactory.h"
#include "Config.h"

#ifdef OPERATIONFACTORY_H

namespace OperationArchitecture
{    
    void OperationFactory::Register(const uint32_t id, IOperationBase*(*factory)(const void *, size_t &))
    {
		if(_factories.find(id) != _factories.end())
			Unregister(id);
		if(_factoriesWithParameters.find(id) != _factoriesWithParameters.end())
			Unregister(id);
		_factories.insert(std::pair<uint32_t, IOperationBase*(*)(const void *, size_t &)>(id, factory));
    }
    
    void OperationFactory::Register(const uint32_t id, ICreateWithParameters *factory)
    {
		if(_factories.find(id) != _factories.end())
			Unregister(id);
		if(_factoriesWithParameters.find(id) != _factoriesWithParameters.end())
			Unregister(id);
		_factoriesWithParameters.insert(std::pair<uint32_t, ICreateWithParameters*>(id, factory));
    }

	void OperationFactory::Unregister(const uint32_t id)
	{
		const std::map<uint32_t, IOperationBase*(*)(const void *, size_t &)>::iterator it = _factories.find(id);
		if (it != _factories.end())
			_factories.erase(it);
            
		const std::map<uint32_t, ICreateWithParameters*>::iterator itWithParameters = _factoriesWithParameters.find(id);
		if (itWithParameters != _factoriesWithParameters.end())
			_factoriesWithParameters.erase(itWithParameters);
	}

    IOperationBase *OperationFactory::Create(const void *config, size_t &sizeOut)
    {
        const uint32_t factoryId = Config::CastAndOffset<uint32_t>(config, sizeOut);

		const std::map<uint32_t, IOperationBase*(*)(const void *, size_t &)>::iterator it = _factories.find(factoryId);
		if (it != _factories.end())
            return it->second(config, sizeOut);
        else 
        {
		    const std::map<uint32_t, ICreateWithParameters*>::iterator itWithParameters = _factoriesWithParameters.find(factoryId);
            if (itWithParameters != _factoriesWithParameters.end())
                return itWithParameters->second->Create(config, sizeOut);
        }

        return 0;
    }
}

#endif