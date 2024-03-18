#include "Operations/Operation.h"
#include "Interpolation.h"
#include "Variable.h"
#include "Config.h"

#ifndef OPERATION_POLYNOMIAL_H
#define OPERATION_POLYNOMIAL_H
namespace OperationArchitecture
{
	template<typename a_t>
	struct Operation_PolynomialConfig
	{
	private:
		Operation_PolynomialConfig()
		{
			
		}
		inline size_t size() const
		{
			const size_t a = alignof(a_t);
			size_t s = sizeof(a_t);
			Config::AlignAndAddSize<a_t>(s);
			Config::AlignAndAddSize<uint8_t>(s);
			if(s % a > 0)
				s += a - (s % a);
			return s;
		}
		
	public:		
		size_t Size() const
		{
			size_t s = size();
			s += sizeof(a_t) * Degree;
			return s;
		}

		const a_t *A() const { return reinterpret_cast<const a_t *>(reinterpret_cast<const uint8_t *>(this) + size()); }

		a_t MinValue;
		a_t MaxValue;
		uint8_t Degree;
	};

	template<typename a_t>
	class Operation_Polynomial : public AbstractOperation
	{
	protected:
		const Operation_PolynomialConfig<a_t> *_config;
	public:		
        Operation_Polynomial(const Operation_PolynomialConfig<a_t> * const &config) :
			AbstractOperation(1, 1)
		{
			_config = config;
		}

		void AbstractExecute(Variable **variables) override
		{
			const a_t x = *variables[1];
			const a_t * a = _config->A();
			a_t val = a[0];
			for (uint8_t i = 1; i <= _config->Degree; i++)
				val += a[i] * powf(x, i);
			if (val < _config->MinValue)
				val = _config->MinValue;
			else if (val > _config->MaxValue)
				val = _config->MaxValue;
			*variables[0] = val;
		}

		static AbstractOperation *Create(const void *config, size_t &sizeOut)
		{
			const Operation_PolynomialConfig<a_t> *polynomialConfig = Config::CastConfigAndOffset<Operation_PolynomialConfig<a_t>>(config, sizeOut);
			return new Operation_Polynomial<a_t>(polynomialConfig);
		}
	};
}
#endif