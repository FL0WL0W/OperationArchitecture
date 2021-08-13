#include <map>
#include <list>
#include "Operations/IOperation.h"
#include <functional>

#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H
namespace OperationArchitecture
{
	class OperationFactory
	{
	protected:
		std::map<uint32_t, IOperationBase*> _operations;
		std::map<uint32_t, std::function<IOperationBase*(const void *, size_t &)>> _factories;
	public:
		void Register(const uint32_t id, std::function<IOperationBase*(const void *, size_t &)> factory);
		void Register(const uint32_t id, IOperationBase* operation);
		void Unregister(const uint32_t id);
		IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif