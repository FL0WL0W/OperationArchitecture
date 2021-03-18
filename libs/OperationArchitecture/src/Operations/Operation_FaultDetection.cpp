#include "Operations/Operation_FaultDetection.h"
#include "Config.h"

#ifdef OPERATION_FAULTDETECTION_H
namespace OperationArchitecture
{
	Operation_FaultDetection::Operation_FaultDetection(const Operation_FaultDetectionConfig * const &config)
	{
		_config = config;
	}

	Variable Operation_FaultDetection::Execute(Variable x)
	{
		float test = x.To<float>();
		if(test < _config->MinValue || test > _config->MaxValue)
		{
			switch(x.Type)
			{
				case UINT8:
					return Variable::Create(static_cast<uint8_t>(_config->DefaultValue));
				case UINT16:
					return Variable::Create(static_cast<uint16_t>(_config->DefaultValue));
				case UINT32:
					return Variable::Create(static_cast<uint32_t>(_config->DefaultValue));
				case UINT64:
					return Variable::Create(static_cast<uint64_t>(_config->DefaultValue));
				case INT8:
					return Variable::Create(static_cast<int8_t>(_config->DefaultValue));
				case INT16:
					return Variable::Create(static_cast<int16_t>(_config->DefaultValue));
				case INT32:
					return Variable::Create(static_cast<int32_t>(_config->DefaultValue));
				case INT64:
					return Variable::Create(static_cast<int64_t>(_config->DefaultValue));
				case FLOAT:
					return Variable::Create(_config->DefaultValue);
				case DOUBLE:
					return Variable::Create(static_cast<double>(_config->DefaultValue));
				case BOOLEAN:
					return Variable::Create(static_cast<bool>(_config->DefaultValue));
				case VariableType::VOID: 
					return Variable();
					//this would be useless to use
			}
		}
		return x;
	}

	IOperationBase *Operation_FaultDetection::Create(const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const Operation_FaultDetectionConfig *faultConfig = Config::CastConfigAndOffset<const Operation_FaultDetectionConfig>(config, sizeOut);
		return new Operation_FaultDetection(faultConfig);
	}
}
#endif