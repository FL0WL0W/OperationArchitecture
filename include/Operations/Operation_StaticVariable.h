#include "Operations/IOperation.h"
#include "Interpolation.h"
#include "Variable.h"

#ifndef OPERATION_STATICVARIABLE_H
#define OPERATION_STATICVARIABLE_H
namespace OperationArchitecture
{
	class Operation_StaticVariable : public IOperationBase
	{
	protected:
        Variable _staticValue;
	public:		
        Operation_StaticVariable(const Variable &staticValue);

		void AbstractExecute(Variable **variables) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif