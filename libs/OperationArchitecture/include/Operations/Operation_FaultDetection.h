#include "Operations/IOperation.h"
#include "Packed.h"
#include "Interpolation.h"
#include "Variable.h"

#ifndef OPERATION_FAULTDETECTION_H
#define OPERATION_FAULTDETECTION_H
namespace OperationArchitecture
{
	PACK(
	struct Operation_FaultDetectionConfig
	{
	public:
		constexpr const unsigned int Size() const
		{
			return sizeof(Operation_FaultDetectionConfig);
		}
		
		float MinValue;
		float MaxValue;
		float DefaultValue;
	});

	class Operation_FaultDetection : public IOperationBase
	{
	protected:
		const Operation_FaultDetectionConfig *_config;
	public:		
        Operation_FaultDetection(const Operation_FaultDetectionConfig * const &config);

		void AbstractExecute(Variable &ret, Variable *params) override;

		static IOperationBase *Create(const void *config, unsigned int &sizeOut);
	};
}
#endif