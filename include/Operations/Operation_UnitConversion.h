#include "Operations/IOperation.h"
#include "Interpolation.h"
#include "Variable.h"
#include "Config.h"

#ifndef OPERATION_UNITCONVERSION_H
#define OPERATION_UNITCONVERSION_H
namespace OperationArchitecture
{
	class Operation_UnitConversion : public IOperationBase
	{
	protected:
		float _multiplier;
		float _adder;
	public:		
        Operation_UnitConversion(const float &multiplier, const float &adder);

		void AbstractExecute(Variable **variables) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif