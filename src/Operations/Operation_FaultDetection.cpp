#include "Operations/Operation_FaultDetection.h"
#include "Config.h"

#ifdef OPERATION_FAULTDETECTION_H
namespace OperationArchitecture
{
	Operation *Operation_FaultDetection::Construct(const Operation_FaultDetectionConfig * const &config)
	{
		return new Operation([config](Variable **variables) 
		{
			float test = variables[1]->To<float>();
			if(test < config->MinValue || test > config->MaxValue)
			{
				switch(variables[1]->Type)
				{
					case UINT8:
						variables[0]->Set(static_cast<uint8_t>(config->DefaultValue));
						break;
					case UINT16:
						variables[0]->Set(static_cast<uint16_t>(config->DefaultValue));
						break;
					case UINT32:
						variables[0]->Set(static_cast<uint32_t>(config->DefaultValue));
						break;
					case UINT64:
						variables[0]->Set(static_cast<uint64_t>(config->DefaultValue));
						break;
					case INT8:
						variables[0]->Set(static_cast<int8_t>(config->DefaultValue));
						break;
					case INT16:
						variables[0]->Set(static_cast<int16_t>(config->DefaultValue));
						break;
					case INT32:
						variables[0]->Set(static_cast<int32_t>(config->DefaultValue));
						break;
					case INT64:
						variables[0]->Set(static_cast<int64_t>(config->DefaultValue));
						break;
					case FLOAT:
						variables[0]->Set(config->DefaultValue);
						break;
					case DOUBLE:
						variables[0]->Set(static_cast<double>(config->DefaultValue));
						break;
					case BOOLEAN:
						variables[0]->Set(static_cast<bool>(config->DefaultValue));
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
		}, 1, 1);
	}

	Operation *Operation_FaultDetection::Create(const void *config, size_t &sizeOut)
	{
		const Operation_FaultDetectionConfig *faultConfig = Config::CastConfigAndOffset<Operation_FaultDetectionConfig>(config, sizeOut);
		return Construct(faultConfig);
	}
}
#endif