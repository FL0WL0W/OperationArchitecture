#include "Operations/OperationFactory.h"
#include "GeneratorMap.h"

#ifndef OPERATIONFACTORYREGISTER_H
#define OPERATIONFACTORYREGISTER_H
namespace OperationArchitecture
{
	class OperationFactoryRegister
	{
		public:
		static void Register(uint32_t idOffset, OperationFactory *factory, GeneratorMap<Variable> *variableMap);
	};
}
#endif