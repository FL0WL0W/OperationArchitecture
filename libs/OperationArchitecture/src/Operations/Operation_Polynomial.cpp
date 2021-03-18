#include "Operations/Operation_Polynomial.h"
#include "Config.h"

#ifdef OPERATION_POLYNOMIAL_H
namespace OperationArchitecture
{
	Operation_Polynomial::Operation_Polynomial(const Operation_PolynomialConfig * const &config)
	{
		_config = config;
	}

	Variable Operation_Polynomial::Execute(Variable xIn)
	{
		const float x = xIn.To<float>();
		const float * a = _config->A();
		float val = a[0];
		for (uint8_t i = 1; i <= _config->Degree; i++)
			val += a[i] * powf(x, i);
		if (val < _config->MinValue)
			val = _config->MinValue;
		else if (val > _config->MaxValue)
			val = _config->MaxValue;
		return Variable::Create(val);
	}

	IOperationBase *Operation_Polynomial::Create(const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const Operation_PolynomialConfig *polynomialConfig = Config::CastConfigAndOffset<const Operation_PolynomialConfig>(config, sizeOut);
		return new Operation_Polynomial(polynomialConfig);
	}
}
#endif