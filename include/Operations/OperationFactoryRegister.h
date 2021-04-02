#include <map>
#include "Operations/OperationFactory.h"

#ifndef OPERATIONFACTORYREGISTER_H
#define OPERATIONFACTORYREGISTER_H
namespace OperationArchitecture
{
	class OperationFactoryRegister
	{
		public:
		static void Register(OperationFactory *factory);
	};
}
#endif