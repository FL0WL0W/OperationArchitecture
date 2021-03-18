#include "Operations/IOperation.h"
#include "Packed.h"
#include "Interpolation.h"
#include "Variable.h"

#ifndef OPERATION_STATICVARIABLE_H
#define OPERATION_STATICVARIABLE_H
namespace OperationArchitecture
{
	class Operation_StaticVariable : public IOperation<Variable>
	{
	protected:
        Variable _staticValue;
	public:		
        Operation_StaticVariable(const Variable &staticValue);

		Variable Execute() override;

		static IOperationBase *Create(const void *config, unsigned int &sizeOut);
	};
}
#endif