#include "Config.h"
#include "Operations/Operation_StaticVariable.h"

#ifdef OPERATION_STATICVARIABLE_H
namespace OperationArchitecture
{
	Operation * Operation_StaticVariable::Create(const void *config, size_t &sizeOut)
	{
		const VariableType staticValueType = Config::CastAndOffset<VariableType>(config, sizeOut);
		switch (staticValueType)
		{
			case VariableType::UINT8:
				return Construct(Config::CastAndOffset<uint8_t>(config, sizeOut));
				break;
			case VariableType::UINT16:
				return Construct(Config::CastAndOffset<uint16_t>(config, sizeOut));
				break;
			case VariableType::UINT32:
				return Construct(Config::CastAndOffset<uint32_t>(config, sizeOut));
				break;
			case VariableType::UINT64:
				return Construct(Config::CastAndOffset<uint64_t>(config, sizeOut));
				break;
			case VariableType::INT8:
				return Construct(Config::CastAndOffset<int8_t>(config, sizeOut));
				break;
			case VariableType::INT16:
				return Construct(Config::CastAndOffset<int16_t>(config, sizeOut));
				break;
			case VariableType::INT32:
				return Construct(Config::CastAndOffset<int32_t>(config, sizeOut));
				break;
			case VariableType::INT64:
				return Construct(Config::CastAndOffset<int64_t>(config, sizeOut));
				break;
			case VariableType::FLOAT:
				return Construct(Config::CastAndOffset<float>(config, sizeOut));
				break;
			case VariableType::DOUBLE:
				return Construct(Config::CastAndOffset<double>(config, sizeOut));
				break;
			case VariableType::BOOLEAN:
				return Construct(Config::CastAndOffset<bool>(config, sizeOut));
				break;
			case VariableType::OTHER:
			{
				Variable staticValue;
				staticValue = Variable::Create(Config::CastAndOffset<uint64_t>(config, sizeOut));
				staticValue.Type = OTHER;
				return Construct(staticValue);
			}
        	case VariableType::BIGOTHER:
			{
				Variable staticValue;
				uint32_t length = Config::CastAndOffset<uint32_t>(config, sizeOut);
				Config::AlignConfig(config, sizeOut, alignof(max_align_t));
				staticValue.Value = *reinterpret_cast<uint64_t *>(&config);
				staticValue.Type = BIGOTHER;
				Config::OffsetConfig(config, sizeOut, length);
				return Construct(staticValue);
			}
        	case VariableType::POINTER:
			case VariableType::VOID: 
				return Construct(0);
		}
	}
}
#endif