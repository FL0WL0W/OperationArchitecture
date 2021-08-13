#include "Operations/OperationFactory.h"

#ifndef OPERATIONPACKAGER_H
#define OPERATIONPACKAGER_H
namespace OperationArchitecture
{
	struct PackageOptions 
	{
		bool OperationImmediate : 1;
		bool StoreVariables : 1;
		bool ReturnVariables : 1;
		bool Group : 1;
		bool DoNotPackage : 1;
	};

	class SystemBus
	{
	public:
		std::map<uint32_t, Operation*> Operations;
		std::map<uint32_t, Variable*> Variables;
		
    	Variable *GetOrCreateVariable(uint32_t variableId);
	};

	class OperationPackager
	{
	protected:
		OperationFactory *_factory;
		SystemBus *_systemBus;
	public:
        OperationPackager(OperationFactory *factory, SystemBus *systemBus);

		Operation *Package(const void *config, size_t &sizeOut);
	};
}
#endif