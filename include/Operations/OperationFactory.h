#include <map>
#include "Operations/IOperation.h"

#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H
namespace OperationArchitecture
{
	class OperationFactory
	{
	protected:
		std::map<uint32_t, IOperationBase*(*)(const void *, unsigned int &)> _factories;
		uint32_t _idOffset;
	public:
		OperationFactory();
		OperationFactory(const uint32_t idOffset);
		void Register(const uint32_t id, IOperationBase*(*factory)(const void *, unsigned int &));
		void Unregister(const uint32_t id);
		IOperationBase *Create(const void *config, unsigned int &sizeOut);
	};
}
#endif