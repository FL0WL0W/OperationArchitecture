#include "Operations/OperationFactory.h"

#ifdef OPERATIONFACTORY_H

namespace OperationArchitecture
{
    OperationFactory::OperationFactory()
    {
        _idOffset = 0;
    }

    OperationFactory::OperationFactory(const uint32_t idOffset)
    {
        _idOffset = idOffset;
    }
    
    void OperationFactory::Register(const uint32_t id, IOperationBase*(*factory)(const void *, unsigned int &))
    {
		if(_factories.find(id) != _factories.end())
			Unregister(id);
		_factories.insert(std::pair<uint32_t, IOperationBase*(*)(const void *, unsigned int &)>(id, factory));
    }

	void OperationFactory::Unregister(const uint32_t id)
	{
		const std::map<uint32_t, IOperationBase*(*)(const void *, unsigned int &)>::iterator it = _factories.find(id);
		if (it != _factories.end())
			_factories.erase(it);
	}

    IOperationBase *OperationFactory::Create(const void *config, unsigned int &sizeOut)
    {
        const uint32_t factoryId = *reinterpret_cast<const uint32_t *>(config) - _idOffset;
        IOperationBase*(*factory)(const void *, unsigned int &);
		const std::map<uint32_t, IOperationBase*(*)(const void *, unsigned int &)>::iterator it = _factories.find(factoryId);
		if (it != _factories.end())
			factory = it->second;
        else 
            return 0;

        return factory(config, sizeOut);
    }
}

#endif