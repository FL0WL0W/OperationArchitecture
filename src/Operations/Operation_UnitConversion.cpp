#include "Config.h"
#include "Operations/Operation_UnitConversion.h"

#ifdef OPERATION_UNITCONVERSION_H
namespace OperationArchitecture
{
	Operation_UnitConversion::Operation_UnitConversion(const float &multiplier, const float &adder) :
		IOperationBase(1, 1), _multiplier(multiplier), _adder(adder) { }


	void Operation_UnitConversion::AbstractExecute(Variable **variables)
	{
		variables[0]->Set(variables[1]->To<float>() * _multiplier + _adder);
	}

	IOperationBase * Operation_UnitConversion::Create(const void *config, size_t &sizeOut)
	{
		return new Operation_UnitConversion(Config::CastAndOffset<float>(config, sizeOut), Config::CastAndOffset<float>(config, sizeOut));
	}
}
#endif