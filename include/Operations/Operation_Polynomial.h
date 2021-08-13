#include "Operations/IOperation.h"
#include "Interpolation.h"
#include "Variable.h"
#include "Config.h"

#ifndef OPERATION_POLYNOMIAL_H
#define OPERATION_POLYNOMIAL_H
namespace OperationArchitecture
{
	struct Operation_PolynomialConfig
	{
	private:
		Operation_PolynomialConfig()
		{
			
		}
		constexpr const size_t size() const
		{
			const size_t a = alignof(float);
			size_t s = sizeof(Operation_PolynomialConfig);
			if(s % a > 0)
				s += a - (s % a);
			return s;
		}
		
	public:		
		constexpr const size_t Size() const
		{
			size_t s = size();
			s += sizeof(float) * Degree;
			return s;
		}

		const float *A() const { return reinterpret_cast<const float *>(reinterpret_cast<const uint8_t *>(this) + size()); }

		float MinValue;
		float MaxValue;
		uint8_t Degree;
	};

	class Operation_Polynomial : public IOperationBase
	{
	protected:
		const Operation_PolynomialConfig *_config;
	public:		
        Operation_Polynomial(const Operation_PolynomialConfig * const &config);

		void AbstractExecute(Variable **variables) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif