#include "Operations/Operation_LookupTable.h"
#include "Config.h"

#ifdef OPERATION_LOOKUPTABLE_H
namespace OperationArchitecture
{
	Operation_LookupTable::Operation_LookupTable(const Operation_LookupTableConfig * const &config)
	{
		_config = config;
	}

	Variable Operation_LookupTable::Execute(Variable x)
	{
		switch(_config->TableType)
		{
			case VariableType::UINT8:
				return Variable::Create(Interpolation::InterpolateTable1<uint8_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint8_t*>(_config->Table())));
			case VariableType::UINT16:
				return Variable::Create(Interpolation::InterpolateTable1<uint16_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint16_t*>(_config->Table())));
			case VariableType::UINT32:
				return Variable::Create(Interpolation::InterpolateTable1<uint16_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint16_t*>(_config->Table())));
			case VariableType::UINT64:
				return Variable::Create(Interpolation::InterpolateTable1<uint64_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const uint64_t*>(_config->Table())));
			case VariableType::INT8:
				return Variable::Create(Interpolation::InterpolateTable1<int8_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int8_t*>(_config->Table())));
			case VariableType::INT16:
				return Variable::Create(Interpolation::InterpolateTable1<int16_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int16_t*>(_config->Table())));
			case VariableType::INT32:
				return Variable::Create(Interpolation::InterpolateTable1<int32_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int32_t*>(_config->Table())));
			case VariableType::INT64:
				return Variable::Create(Interpolation::InterpolateTable1<int64_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const int64_t*>(_config->Table())));
			case VariableType::FLOAT:
				return Variable::Create(Interpolation::InterpolateTable1<float>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const float*>(_config->Table())));
			case VariableType::DOUBLE:
				return Variable::Create(Interpolation::InterpolateTable1<double>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const double*>(_config->Table())));
			case VariableType::BOOLEAN:
				return Variable::Create(Interpolation::InterpolateTable1<bool>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, reinterpret_cast<const bool*>(_config->Table())));
			case VariableType::VOID: 
				return Variable();
				//this would be useless to use
		}
		return Variable();
	}

	IOperationBase *Operation_LookupTable::Create(const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const Operation_LookupTableConfig *tableConfig = Config::CastConfigAndOffset<const Operation_LookupTableConfig>(config, sizeOut);
		return new Operation_LookupTable(tableConfig);
	}
}
#endif