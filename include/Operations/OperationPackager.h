#include "Operations/OperationFactory.h"
#include "Operations/Operation_Package.h"

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
		std::map<uint32_t, IOperationBase*> Operations;
		std::map<uint32_t, Variable*> Variables;
		
    	Variable *GetOrCreateVariable(uint32_t variableId);
	};

	class OperationPackager
	{
	protected:
		OperationFactory *_factory;
		SystemBus *_systemBus;

    	OperationOrVariable CreateParameter(const void *config, size_t &sizeOut);
	public:
        OperationPackager(OperationFactory *factory, SystemBus *systemBus);

		IOperationBase *Package(const void *config, size_t &sizeOut);
	};
}
#endif