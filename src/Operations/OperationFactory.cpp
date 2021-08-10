#include "Operations/OperationFactory.h"
#include "Config.h"

#ifdef OPERATIONFACTORY_H

namespace OperationArchitecture
{    
    void OperationFactory::Register(const uint32_t id, std::function<IOperationBase*(const void *, size_t &)> factory)
    {
		if(_factories.find(id) != _factories.end())
			Unregister(id);
		_factories.insert(std::pair<uint32_t, std::function<IOperationBase*(const void *, size_t &)>>(id, factory));
    }

	void OperationFactory::Unregister(const uint32_t id)
	{
		const std::map<uint32_t, std::function<IOperationBase*(const void *, size_t &)>>::iterator it = _factories.find(id);
		if (it != _factories.end())
			_factories.erase(it);
	}

    IOperationBase *OperationFactory::Create(const void *config, size_t &sizeOut)
    {
        const uint32_t factoryId = Config::CastAndOffset<uint32_t>(config, sizeOut);

		const std::map<uint32_t, std::function<IOperationBase*(const void *, size_t &)>>::iterator it = _factories.find(factoryId);
		if (it != _factories.end())
            return it->second(config, sizeOut);

        return 0;
    }
}

#endif