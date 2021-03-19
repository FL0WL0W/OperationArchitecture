#include "Operations/Operation_2AxisTable.h"
#include "Config.h"

#ifdef OPERATION_2AXISTABLE_H
namespace OperationArchitecture
{
	Operation_2AxisTable::Operation_2AxisTable(const Operation_2AxisTableConfig * const &config)
	{
        NumberOfParameters = 2;
        ReturnsVariable = true;
		_config = config;
	}

	void Operation_2AxisTable::AbstractExecute(Variable &ret, Variable *params)
	{
		switch(_config->TableType)
		{
			case VariableType::UINT8:
				ret.Set(Interpolation::InterpolateTable2<uint8_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint8_t*>(_config->Table())));
				break;
			case VariableType::UINT16:
				ret.Set(Interpolation::InterpolateTable2<uint16_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint16_t*>(_config->Table())));
				break;
			case VariableType::UINT32:
				ret.Set(Interpolation::InterpolateTable2<uint32_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint32_t*>(_config->Table())));
				break;
			case VariableType::UINT64:
				ret.Set(Interpolation::InterpolateTable2<uint64_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint64_t*>(_config->Table())));
				break;
			case VariableType::INT8:
				ret.Set(Interpolation::InterpolateTable2<int8_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int8_t*>(_config->Table())));
				break;
			case VariableType::INT16:
				ret.Set(Interpolation::InterpolateTable2<int16_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int16_t*>(_config->Table())));
				break;
			case VariableType::INT32:
				ret.Set(Interpolation::InterpolateTable2<int32_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int32_t*>(_config->Table())));
				break;
			case VariableType::INT64:
				ret.Set(Interpolation::InterpolateTable2<int64_t>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int64_t*>(_config->Table())));
				break;
			case VariableType::FLOAT:
				ret.Set(Interpolation::InterpolateTable2<float>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const float*>(_config->Table())));
				break;
			case VariableType::DOUBLE:
				ret.Set(Interpolation::InterpolateTable2<double>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const double*>(_config->Table())));
				break;
			case VariableType::BOOLEAN:
				ret.Set(Interpolation::InterpolateTable2<bool>(params[0].To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, params[1].To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const bool*>(_config->Table())));
				break;
			default:
				//should throw here
				break;
		}
	}

	IOperationBase * Operation_2AxisTable::Create(const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const Operation_2AxisTableConfig *tableConfig = Config::CastConfigAndOffset<const Operation_2AxisTableConfig>(config, sizeOut);
		return new Operation_2AxisTable(tableConfig);
	}
}
#endif