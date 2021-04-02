#include "Operations/OperationFactory.h"
#include "Config.h"

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
    
    void OperationFactory::RegisterSubFactory(IOperationFactory *subFactory)
    {
        _subFactories.push_back(subFactory);
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
            return it->second(config, sizeOut);
        else 
        {
            for (IOperationFactory *subFactory : _subFactories) 
            {
                unsigned int size = 0;
                IOperationBase* ret = subFactory->Create(config, size);
                if(size > 0)
                {
                    Config::OffsetConfig(config, sizeOut, size);
                    return ret;
                }
            }
        }
    }
}

#endif