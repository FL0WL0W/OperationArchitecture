#include <map>
#include <list>
#include "Operations/Operation.h"
#include <functional>

#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H
namespace OperationArchitecture
{
	class OperationFactory
	{
	protected:
		std::map<uint32_t, std::function<Operation*(const void *, size_t &)>> _factories;
	public:
		void Register(const uint32_t id, std::function<Operation*(const void *, size_t &)> factory);
		void Unregister(const uint32_t id);
		Operation *Create(const void *config, size_t &sizeOut);
	};
}
#endif