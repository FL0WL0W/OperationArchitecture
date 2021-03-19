#include "Operations/OperationFactory.h"
#include "Operations/Operation_Package.h"

#ifndef OPERATIONPACKAGER_H
#define OPERATIONPACKAGER_H
namespace OperationArchitecture
{
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

    	OperationOrVariable CreateParameter(const void *config, unsigned int &sizeOut);
    	OperationOrVariable* CreateParameters(const uint8_t numberOfParameters, const void *config, unsigned int &sizeOut);
	public:
        OperationPackager(OperationFactory *factory, SystemBus *systemBus);

		IOperationBase *Package(const void *config, unsigned int &sizeOut);
	};
}
#endif