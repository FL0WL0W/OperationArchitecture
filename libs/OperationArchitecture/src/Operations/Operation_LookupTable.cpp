#include "Operations/Operation_LookupTable.h"
#include "Config.h"

#ifdef OPERATION_LOOKUPTABLE_H
namespace OperationArchitecture
{
	Operation_LookupTable::Operation_LookupTable(const Operation_LookupTableConfig * const &config)
	{
        NumberOfParameters = 1;
        ReturnsVariable = true;
		_config = config;
	}

	void Operation_LookupTable::AbstractExecute(Variable &ret, Variable *params)
	{
		switch(_config->TableType)
		{
			case VariableType::UINT8:
				ret.Set(Interpolation::InterpolateTable1<uint8_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint8_t*>(_config->Table())));
				break;
			case VariableType::UINT16:
				ret.Set(Interpolation::InterpolateTable1<uint16_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint16_t*>(_config->Table())));
				break;
			case VariableType::UINT32:
				ret.Set(Interpolation::InterpolateTable1<uint16_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint16_t*>(_config->Table())));
				break;
			case VariableType::UINT64:
				ret.Set(Interpolation::InterpolateTable1<uint64_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint64_t*>(_config->Table())));
				break;
			case VariableType::INT8:
				ret.Set(Interpolation::InterpolateTable1<int8_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int8_t*>(_config->Table())));
				break;
			case VariableType::INT16:
				ret.Set(Interpolation::InterpolateTable1<int16_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int16_t*>(_config->Table())));
				break;
			case VariableType::INT32:
				ret.Set(Interpolation::InterpolateTable1<int32_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int32_t*>(_config->Table())));
				break;
			case VariableType::INT64:
				ret.Set(Interpolation::InterpolateTable1<int64_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int64_t*>(_config->Table())));
				break;
			case VariableType::FLOAT:
				ret.Set(Interpolation::InterpolateTable1<float>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const float*>(_config->Table())));
				break;
			case VariableType::DOUBLE:
				ret.Set(Interpolation::InterpolateTable1<double>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const double*>(_config->Table())));
				break;
			case VariableType::BOOLEAN:
				ret.Set(Interpolation::InterpolateTable1<bool>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const bool*>(_config->Table())));
				break;
			default:
				//should throw here
				break;
		}
	}

	IOperationBase *Operation_LookupTable::Create(const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const Operation_LookupTableConfig *tableConfig = Config::CastConfigAndOffset<const Operation_LookupTableConfig>(config, sizeOut);
		return new Operation_LookupTable(tableConfig);
	}
}
#endif