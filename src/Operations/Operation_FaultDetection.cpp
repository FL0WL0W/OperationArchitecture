#include "Operations/Operation_FaultDetection.h"
#include "Config.h"

#ifdef OPERATION_FAULTDETECTION_H
namespace OperationArchitecture
{
	Operation_FaultDetection::Operation_FaultDetection(const Operation_FaultDetectionConfig * const &config)
	{
		NumberOfReturnVariables = 1;
        NumberOfParameters = 1;
		_config = config;
	}

	void Operation_FaultDetection::AbstractExecute(Variable **variables)
	{
		float test = variables[1]->To<float>();
		if(test < _config->MinValue || test > _config->MaxValue)
		{
			switch(variables[1]->Type)
			{
				case UINT8:
					variables[0]->Set(static_cast<uint8_t>(_config->DefaultValue));
					break;
				case UINT16:
					variables[0]->Set(static_cast<uint16_t>(_config->DefaultValue));
					break;
				case UINT32:
					variables[0]->Set(static_cast<uint32_t>(_config->DefaultValue));
					break;
				case UINT64:
					variables[0]->Set(static_cast<uint64_t>(_config->DefaultValue));
					break;
				case INT8:
					variables[0]->Set(static_cast<int8_t>(_config->DefaultValue));
					break;
				case INT16:
					variables[0]->Set(static_cast<int16_t>(_config->DefaultValue));
					break;
				case INT32:
					variables[0]->Set(static_cast<int32_t>(_config->DefaultValue));
					break;
				case INT64:
					variables[0]->Set(static_cast<int64_t>(_config->DefaultValue));
					break;
				case FLOAT:
					variables[0]->Set(_config->DefaultValue);
					break;
				case DOUBLE:
					variables[0]->Set(static_cast<double>(_config->DefaultValue));
					break;
				case BOOLEAN:
					variables[0]->Set(static_cast<bool>(_config->DefaultValue));
					break;
				default:
					//should throw here
					break;
			}
		}
		else
		{
			variables[0]->Set(*variables[1]);
		}
	}

	IOperationBase *Operation_FaultDetection::Create(const void *config, unsigned int &sizeOut)
	{
		const Operation_FaultDetectionConfig *faultConfig = Config::CastConfigAndOffset<Operation_FaultDetectionConfig>(config, sizeOut);
		return new Operation_FaultDetection(faultConfig);
	}
}
#endif