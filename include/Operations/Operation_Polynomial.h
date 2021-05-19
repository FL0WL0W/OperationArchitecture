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
		
	public:		
		constexpr const size_t Size() const
		{
			return sizeof(Operation_PolynomialConfig) + 
				((sizeof(Operation_PolynomialConfig) % alignof(float) > 0)? (alignof(float) - (sizeof(Operation_PolynomialConfig) % alignof(float))) : 0) + 
				sizeof(float) * (Degree + 1);
		}

		const float *A() const { return reinterpret_cast<const float *>(Config::AlignConfig(this + 1, alignof(float))); }

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