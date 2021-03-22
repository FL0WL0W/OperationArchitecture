#include "Operations/Operation_LookupTable.h"
#include "Config.h"

#ifdef OPERATION_LOOKUPTABLE_H
namespace OperationArchitecture
{
	Operation_LookupTable::Operation_LookupTable(const Operation_LookupTableConfig * const &config)
	{
        NumberOfReturnVariables = 1;
        NumberOfParameters = 1;
		_config = config;
	}

	void Operation_LookupTable::AbstractExecute(Variable **variables)
	{
		switch(_config->TableType)
		{
			case VariableType::UINT8:
				variables[0]->Set(Interpolation::InterpolateTable1<uint8_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint8_t*>(_config->Table())));
				break;
			case VariableType::UINT16:
				variables[0]->Set(Interpolation::InterpolateTable1<uint16_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint16_t*>(_config->Table())));
				break;
			case VariableType::UINT32:
				variables[0]->Set(Interpolation::InterpolateTable1<uint16_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint16_t*>(_config->Table())));
				break;
			case VariableType::UINT64:
				variables[0]->Set(Interpolation::InterpolateTable1<uint64_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint64_t*>(_config->Table())));
				break;
			case VariableType::INT8:
				variables[0]->Set(Interpolation::InterpolateTable1<int8_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int8_t*>(_config->Table())));
				break;
			case VariableType::INT16:
				variables[0]->Set(Interpolation::InterpolateTable1<int16_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int16_t*>(_config->Table())));
				break;
			case VariableType::INT32:
				variables[0]->Set(Interpolation::InterpolateTable1<int32_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int32_t*>(_config->Table())));
				break;
			case VariableType::INT64:
				variables[0]->Set(Interpolation::InterpolateTable1<int64_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int64_t*>(_config->Table())));
				break;
			case VariableType::FLOAT:
				variables[0]->Set(Interpolation::InterpolateTable1<float>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const float*>(_config->Table())));
				break;
			case VariableType::DOUBLE:
				variables[0]->Set(Interpolation::InterpolateTable1<double>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const double*>(_config->Table())));
				break;
			case VariableType::BOOLEAN:
				variables[0]->Set(Interpolation::InterpolateTable1<bool>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const bool*>(_config->Table())));
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