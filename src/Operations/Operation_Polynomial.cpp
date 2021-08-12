#include "Operations/Operation_Polynomial.h"

#ifdef OPERATION_POLYNOMIAL_H
namespace OperationArchitecture
{
	Operation *Operation_Polynomial::Construct(const Operation_PolynomialConfig * const &config)
	{
		return new Operation([config](Variable **variables) 
		{
			const float x = variables[1]->To<float>();
			const float * a = config->A();
			float val = a[0];
			for (uint8_t i = 1; i <= config->Degree; i++)
				val += a[i] * powf(x, i);
			if (val < config->MinValue)
				val = config->MinValue;
			else if (val > config->MaxValue)
				val = config->MaxValue;
			variables[0]->Set(val);
		}, 1, 1);
	}

	Operation *Operation_Polynomial::Create(const void *config, size_t &sizeOut)
	{
		const Operation_PolynomialConfig *polynomialConfig = Config::CastConfigAndOffset<Operation_PolynomialConfig>(config, sizeOut);
		return Construct(polynomialConfig);
	}
}
#endif