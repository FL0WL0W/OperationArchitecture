#include <map>
#include <list>
#include "Operations/IOperation.h"
#include "CreateWithParameters.h"

#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H
namespace OperationArchitecture
{
	class OperationFactory
	{
	protected:
		std::map<uint32_t, IOperationBase*(*)(const void *, unsigned int &)> _factories;
		std::map<uint32_t, ICreateWithParameters*> _factoriesWithParameters;
	public:
		void Register(const uint32_t id, IOperationBase*(*factory)(const void *, unsigned int &));
		void Register(const uint32_t id, ICreateWithParameters *factory);
		void Unregister(const uint32_t id);
		IOperationBase *Create(const void *config, unsigned int &sizeOut);
	};
}
#endif