#include <map>
#include <list>
#include <functional>
#include "Operations/AbstractOperation.h"

#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H
namespace OperationArchitecture
{
	class OperationFactory
	{
	protected:
		std::map<uint32_t, AbstractOperation*> _staticOperations;
		std::list<AbstractOperation*> _dynamicOperations;
		std::map<uint32_t, std::function<AbstractOperation*(const void *, size_t &)>> _factories;
	public:
		~OperationFactory();
		void Clear();
		void Register(const uint32_t id, std::function<AbstractOperation*(const void *, size_t &)> factory);
		void Register(const uint32_t id, AbstractOperation* operation);
		void Unregister(const uint32_t id);
		AbstractOperation *Create(const void *config, size_t &sizeOut);
	};
}
#endif