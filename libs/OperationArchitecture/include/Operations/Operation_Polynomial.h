#include "Operations/IOperation.h"
#include "Packed.h"
#include "Interpolation.h"
#include "Variable.h"

#ifndef OPERATION_POLYNOMIAL_H
#define OPERATION_POLYNOMIAL_H
namespace OperationArchitecture
{
	PACK(
	struct Operation_PolynomialConfig
	{
	private:
		Operation_PolynomialConfig()
		{
			
		}
		
	public:		
		constexpr const unsigned int Size() const
		{
			return sizeof(Operation_PolynomialConfig) + sizeof(float) * (Degree + 1);
		}

		const float *A() const { return reinterpret_cast<const float *>(this + 1); }

		float MinValue;
		float MaxValue;
		uint8_t Degree;
	});

	class Operation_Polynomial : public IOperation<Variable, Variable>
	{
	protected:
		const Operation_PolynomialConfig *_config;
	public:		
        Operation_Polynomial(const Operation_PolynomialConfig * const &config);

		Variable Execute(Variable x) override;

		static IOperationBase *Create(const void *config, unsigned int &sizeOut);
	};
}
#endif