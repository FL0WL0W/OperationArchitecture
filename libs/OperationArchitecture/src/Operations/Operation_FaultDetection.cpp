#include "Operations/Operation_FaultDetection.h"
#include "Config.h"

#ifdef OPERATION_FAULTDETECTION_H
namespace OperationArchitecture
{
	Operation_FaultDetection::Operation_FaultDetection(const Operation_FaultDetectionConfig * const &config)
	{
        NumberOfParameters = 1;
        ReturnsVariable = true;
		_config = config;
	}

	void Operation_FaultDetection::AbstractExecute(Variable &ret, Variable *params)
	{
		float test = params[0].To<float>();
		if(test < _config->MinValue || test > _config->MaxValue)
		{
			switch(params[0].Type)
			{
				case UINT8:
					ret.Set(static_cast<uint8_t>(_config->DefaultValue));
					break;
				case UINT16:
					ret.Set(static_cast<uint16_t>(_config->DefaultValue));
					break;
				case UINT32:
					ret.Set(static_cast<uint32_t>(_config->DefaultValue));
					break;
				case UINT64:
					ret.Set(static_cast<uint64_t>(_config->DefaultValue));
					break;
				case INT8:
					ret.Set(static_cast<int8_t>(_config->DefaultValue));
					break;
				case INT16:
					ret.Set(static_cast<int16_t>(_config->DefaultValue));
					break;
				case INT32:
					ret.Set(static_cast<int32_t>(_config->DefaultValue));
					break;
				case INT64:
					ret.Set(static_cast<int64_t>(_config->DefaultValue));
					break;
				case FLOAT:
					ret.Set(_config->DefaultValue);
					break;
				case DOUBLE:
					ret.Set(static_cast<double>(_config->DefaultValue));
					break;
				case BOOLEAN:
					ret.Set(static_cast<bool>(_config->DefaultValue));
					break;
				default:
					//should throw here
					break;
			}
		}
		else
		{
			ret.Set(params[0]);
		}
	}

	IOperationBase *Operation_FaultDetection::Create(const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const Operation_FaultDetectionConfig *faultConfig = Config::CastConfigAndOffset<const Operation_FaultDetectionConfig>(config, sizeOut);
		return new Operation_FaultDetection(faultConfig);
	}
}
#endif