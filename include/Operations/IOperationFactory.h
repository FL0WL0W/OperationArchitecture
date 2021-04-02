#include <map>
#include <list>
#include "Operations/IOperation.h"

#ifndef IOPERATIONFACTORY_H
#define IOPERATIONFACTORY_H
namespace OperationArchitecture
{
	class IOperationFactory
	{
	public:
		virtual IOperationBase *Create(const void *config, unsigned int &sizeOut) = 0;
	};
}
#endif