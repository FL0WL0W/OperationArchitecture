#include "Operations/Operation.h"
#include "Interpolation.h"
#include "Variable.h"

#ifndef OPERATION_STATICVARIABLE_H
#define OPERATION_STATICVARIABLE_H
namespace OperationArchitecture
{
	class Operation_StaticVariable
	{
	public:		
		template<typename ValueType>
		static Operation *Construct(const ValueType staticValue)
		{
			return new Operation([staticValue](Variable **variables) { variables[0]->Set(staticValue); }, 1, 0);
		}
		static Operation *Create(const void *config, size_t &sizeOut);
	};
}
#endif