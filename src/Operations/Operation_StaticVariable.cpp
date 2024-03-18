#include "Config.h"
#include "Operations/Operation_StaticVariable.h"

#ifdef OPERATION_STATICVARIABLE_H
namespace OperationArchitecture
{
	Operation_StaticVariable::Operation_StaticVariable(const Variable &staticValue) :
		AbstractOperation(1, 0), _staticValue(staticValue) {}

	void Operation_StaticVariable::AbstractExecute(Variable **variables)
	{
		*variables[0] = _staticValue;
	}

	AbstractOperation * Operation_StaticVariable::Create(const void *config, size_t &sizeOut)
	{
		const VariableType staticValueType = Config::CastAndOffset<VariableType>(config, sizeOut);
		Variable staticValue;
		switch (staticValueType)
		{
			case VariableType::UINT8:
				staticValue = Config::CastAndOffset<uint8_t>(config, sizeOut);
				break;
			case VariableType::UINT16:
				staticValue = Config::CastAndOffset<uint16_t>(config, sizeOut);
				break;
			case VariableType::UINT32:
				staticValue = Config::CastAndOffset<uint32_t>(config, sizeOut);
				break;
			case VariableType::UINT64:
				staticValue = Config::CastAndOffset<uint64_t>(config, sizeOut);
				break;
			case VariableType::INT8:
				staticValue = Config::CastAndOffset<int8_t>(config, sizeOut);
				break;
			case VariableType::INT16:
				staticValue = Config::CastAndOffset<int16_t>(config, sizeOut);
				break;
			case VariableType::INT32:
				staticValue = Config::CastAndOffset<int32_t>(config, sizeOut);
				break;
			case VariableType::INT64:
				staticValue = Config::CastAndOffset<int64_t>(config, sizeOut);
				break;
			case VariableType::FLOAT:
				staticValue = Config::CastAndOffset<float>(config, sizeOut);
				break;
			case VariableType::DOUBLE:
				staticValue = Config::CastAndOffset<double>(config, sizeOut);
				break;
			case VariableType::BOOLEAN:
				staticValue = Config::CastAndOffset<bool>(config, sizeOut);
				break;
			case VariableType::OTHER:
				staticValue = Config::CastAndOffset<uint64_t>(config, sizeOut);
				staticValue.Type = OTHER;
				break;
        	case VariableType::BIGOTHER:
			{
				uint32_t length = Config::CastAndOffset<uint32_t>(config, sizeOut);
				Config::AlignConfig(config, sizeOut, alignof(max_align_t));
				staticValue = config;
				staticValue.Type = BIGOTHER;
				Config::OffsetConfig(config, sizeOut, length);
				break;
			}
        	case VariableType::POINTER:
			case VariableType::VOID: 
				//this would be useless to create
				break;
		}
		
		return new Operation_StaticVariable(staticValue);
	}
}
#endif