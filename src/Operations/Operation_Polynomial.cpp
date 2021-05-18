#include "Operations/Operation_Polynomial.h"
#include "Config.h"

#ifdef OPERATION_POLYNOMIAL_H
namespace OperationArchitecture
{
	Operation_Polynomial::Operation_Polynomial(const Operation_PolynomialConfig * const &config)
	{
		NumberOfReturnVariables = 1;
        NumberOfParameters = 1;
		_config = config;
	}

	void Operation_Polynomial::AbstractExecute(Variable **variables)
	{
		const float x = variables[1]->To<float>();
		const float * a = _config->A();
		float val = a[0];
		for (uint8_t i = 1; i <= _config->Degree; i++)
			val += a[i] * powf(x, i);
		if (val < _config->MinValue)
			val = _config->MinValue;
		else if (val > _config->MaxValue)
			val = _config->MaxValue;
		variables[0]->Set(val);
	}

	IOperationBase *Operation_Polynomial::Create(const void *config, size_t &sizeOut)
	{
		const Operation_PolynomialConfig *polynomialConfig = Config::CastConfigAndOffset<Operation_PolynomialConfig>(config, sizeOut);
		return new Operation_Polynomial(polynomialConfig);
	}
}
#endif