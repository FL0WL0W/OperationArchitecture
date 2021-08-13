#include "Operations/IOperation.h"
#include "Interpolation.h"
#include "Variable.h"

#ifndef OPERATION_FAULTDETECTION_H
#define OPERATION_FAULTDETECTION_H
namespace OperationArchitecture
{
	struct Operation_FaultDetectionConfig
	{
	public:
		constexpr const size_t Size() const
		{
			return sizeof(Operation_FaultDetectionConfig);
		}
		
		float MinValue;
		float MaxValue;
		float DefaultValue;
	};

	class Operation_FaultDetection : public IOperationBase
	{
	protected:
		const Operation_FaultDetectionConfig * const _config;
	public:		
        Operation_FaultDetection(const Operation_FaultDetectionConfig * const &config);

		void AbstractExecute(Variable **variables) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut);
	};
}
#endif