#include "Operations/Operation_2AxisTable.h"
#include "Config.h"

#ifdef OPERATION_2AXISTABLE_H
namespace OperationArchitecture
{
	Operation_2AxisTable::Operation_2AxisTable(const Operation_2AxisTableConfig * const &config)
	{
		_config = config;
	}

	Variable Operation_2AxisTable::Execute(Variable x, Variable y)
	{
		switch(_config->TableType)
		{
			case VariableType::UINT8:
				return Variable::Create(Interpolation::InterpolateTable2<uint8_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint8_t*>(_config->Table())));
			case VariableType::UINT16:
				return Variable::Create(Interpolation::InterpolateTable2<uint16_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint16_t*>(_config->Table())));
			case VariableType::UINT32:
				return Variable::Create(Interpolation::InterpolateTable2<uint32_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint32_t*>(_config->Table())));
			case VariableType::UINT64:
				return Variable::Create(Interpolation::InterpolateTable2<uint64_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint64_t*>(_config->Table())));
			case VariableType::INT8:
				return Variable::Create(Interpolation::InterpolateTable2<int8_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int8_t*>(_config->Table())));
			case VariableType::INT16:
				return Variable::Create(Interpolation::InterpolateTable2<int16_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int16_t*>(_config->Table())));
			case VariableType::INT32:
				return Variable::Create(Interpolation::InterpolateTable2<int32_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int32_t*>(_config->Table())));
			case VariableType::INT64:
				return Variable::Create(Interpolation::InterpolateTable2<int64_t>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int64_t*>(_config->Table())));
			case VariableType::FLOAT:
				return Variable::Create(Interpolation::InterpolateTable2<float>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const float*>(_config->Table())));
			case VariableType::DOUBLE:
				return Variable::Create(Interpolation::InterpolateTable2<double>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const double*>(_config->Table())));
			case VariableType::BOOLEAN:
				return Variable::Create(Interpolation::InterpolateTable2<bool>(x.To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, y.To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const bool*>(_config->Table())));
			case VariableType::VOID: 
				return Variable();
				//this would be useless to use
		}
		return Variable();
	}

	IOperationBase * Operation_2AxisTable::Create(const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		const Operation_2AxisTableConfig *tableConfig = Config::CastConfigAndOffset<const Operation_2AxisTableConfig>(config, sizeOut);
		return new Operation_2AxisTable(tableConfig);
	}
}
#endif