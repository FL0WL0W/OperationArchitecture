#include <map>
#include <list>
#include "Operations/IOperation.h"
#include "Operations/IOperationFactory.h"

#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H
namespace OperationArchitecture
{
	class OperationFactory : public IOperationFactory
	{
	protected:
		std::map<uint32_t, IOperationBase*(*)(const void *, unsigned int &)> _factories;
		std::list<IOperationFactory *> _subFactories;
		uint32_t _idOffset;
	public:
		OperationFactory();
		OperationFactory(const uint32_t idOffset);
		void Register(const uint32_t id, IOperationBase*(*factory)(const void *, unsigned int &));
		void RegisterSubFactory(IOperationFactory *subFactory);
		void Unregister(const uint32_t id);
		IOperationBase *Create(const void *config, unsigned int &sizeOut) override;
	};
}
#endif