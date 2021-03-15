#include "Operations/IOperation.h"
#include "Service/ServiceLocator.h"
#include "Packed.h"
#include "Interpolation.h"
#include "Variable.h"

#ifndef OPERATION_STATICSCALAR_H
#define OPERATION_STATICSCALAR_H
namespace OperationArchitecture
{
	class Operation_StaticScalar : public IOperation<Variable>
	{
	protected:
        Variable _staticValue;
	public:		
        Operation_StaticScalar(const Variable &staticValue);

		Variable Execute() override;

		static IOperationBase *Create(const void *config, unsigned int &sizeOut);
	};
}
#endif