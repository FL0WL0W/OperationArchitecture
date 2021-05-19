#include "Operations/Operation_2AxisTable.h"

#ifdef OPERATION_2AXISTABLE_H
namespace OperationArchitecture
{
	Operation_2AxisTable::Operation_2AxisTable(const Operation_2AxisTableConfig * const &config)
	{
		NumberOfReturnVariables = 1;
        NumberOfParameters = 2;
		_config = config;
	}

	void Operation_2AxisTable::AbstractExecute(Variable **variables)
	{
		switch(_config->TableType)
		{
			case VariableType::UINT8:
				variables[0]->Set(Interpolation::InterpolateTable2<uint8_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint8_t*>(_config->Table())));
				break;
			case VariableType::UINT16:
				variables[0]->Set(Interpolation::InterpolateTable2<uint16_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint16_t*>(_config->Table())));
				break;
			case VariableType::UINT32:
				variables[0]->Set(Interpolation::InterpolateTable2<uint32_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint32_t*>(_config->Table())));
				break;
			case VariableType::UINT64:
				variables[0]->Set(Interpolation::InterpolateTable2<uint64_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const uint64_t*>(_config->Table())));
				break;
			case VariableType::INT8:
				variables[0]->Set(Interpolation::InterpolateTable2<int8_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int8_t*>(_config->Table())));
				break;
			case VariableType::INT16:
				variables[0]->Set(Interpolation::InterpolateTable2<int16_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int16_t*>(_config->Table())));
				break;
			case VariableType::INT32:
				variables[0]->Set(Interpolation::InterpolateTable2<int32_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int32_t*>(_config->Table())));
				break;
			case VariableType::INT64:
				variables[0]->Set(Interpolation::InterpolateTable2<int64_t>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const int64_t*>(_config->Table())));
				break;
			case VariableType::FLOAT:
				variables[0]->Set(Interpolation::InterpolateTable2<float>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const float*>(_config->Table())));
				break;
			case VariableType::DOUBLE:
				variables[0]->Set(Interpolation::InterpolateTable2<double>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const double*>(_config->Table())));
				break;
			case VariableType::BOOLEAN:
				variables[0]->Set(Interpolation::InterpolateTable2<bool>(variables[1]->To<float>(), _config->MaxXValue, _config->MinXValue, _config->XResolution, variables[2]->To<float>(), _config->MaxYValue, _config->MinYValue, _config->YResolution, reinterpret_cast<const bool*>(_config->Table())));
				break;
			default:
				//should throw here
				break;
		}
	}

	IOperationBase * Operation_2AxisTable::Create(const void *config, size_t &sizeOut)
	{
		const Operation_2AxisTableConfig *tableConfig = Config::CastConfigAndOffset<Operation_2AxisTableConfig>(config, sizeOut);
		return new Operation_2AxisTable(tableConfig);
	}
}
#endif