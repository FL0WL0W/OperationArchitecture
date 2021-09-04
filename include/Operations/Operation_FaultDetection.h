#include "Operations/IOperation.h"
#include "Interpolation.h"
#include "Variable.h"
#include "Config.h"

#ifndef OPERATION_FAULTDETECTION_H
#define OPERATION_FAULTDETECTION_H
namespace OperationArchitecture
{
	struct Operation_FaultDetectionConfig
	{
	public:
		size_t Size() const
		{
			size_t s = sizeof(float);
			Config::AlignAndAddSize<float>(s);
			Config::AlignAndAddSize<float>(s);
			return s;
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