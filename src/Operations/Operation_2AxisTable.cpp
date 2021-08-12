#include "Operations/Operation_2AxisTable.h"

#ifdef OPERATION_2AXISTABLE_H
namespace OperationArchitecture
{
	Operation *Operation_2AxisTable::Construct(const Operation_2AxisTableConfig * const &tableConfig)
	{
		std::function<void(Variable **)> function;
				
		switch(tableConfig->TableType)
		{
			case VariableType::UINT8:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const uint8_t>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const uint8_t*>(tableConfig->Table())
						)
					);	
				};
				break;
			case VariableType::UINT16:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const uint16_t>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const uint16_t*>(tableConfig->Table())
						)
					);	
				};
				break;
			case VariableType::UINT32:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const uint32_t>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const uint32_t*>(tableConfig->Table())
						)
					);	
				};
				break;
			case VariableType::UINT64:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const uint64_t>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const uint64_t*>(tableConfig->Table())
						)
					);	
				};
				break;
			case VariableType::INT8:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const int8_t>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const int8_t*>(tableConfig->Table())
						)
					);	
				};
				break;
			case VariableType::INT16:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const int16_t>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const int16_t*>(tableConfig->Table())
						)
					);	
				};
				break;
			case VariableType::INT32:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const int32_t>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const int32_t*>(tableConfig->Table())
						)
					);	
				};
				break;
			case VariableType::INT64:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const int64_t>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const int64_t*>(tableConfig->Table())
						)
					);	
				};
				break;
			case VariableType::FLOAT:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const float>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const float*>(tableConfig->Table())
						)
					);	
				};
				break;
			case VariableType::DOUBLE:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const double>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const double*>(tableConfig->Table())
						)
					);	
				};
				break;
			case VariableType::BOOLEAN:
				function = [tableConfig](Variable **variables) 
				{ 
					variables[0]->Set(
						Interpolation::InterpolateTable2<const bool>(
							variables[1]->To<float>(), 
							tableConfig->MaxXValue, 
							tableConfig->MinXValue, 
							tableConfig->XResolution, 
							variables[2]->To<float>(), 
							tableConfig->MaxYValue, 
							tableConfig->MinYValue, 
							tableConfig->YResolution, 
							reinterpret_cast<const bool*>(tableConfig->Table())
						)
					);	
				};
				break;
			default:
				//should throw here
				break;
		}
		
		return new Operation(function, 1, 2);
	}
	
	Operation *Operation_2AxisTable::Create(const void *config, size_t &sizeOut)
	{
		const Operation_2AxisTableConfig *tableConfig = Config::CastConfigAndOffset<Operation_2AxisTableConfig>(config, sizeOut);
		return Construct(tableConfig);
	}
}
#endif