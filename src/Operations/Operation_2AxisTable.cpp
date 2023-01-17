#include "Operations/Operation_2AxisTable.h"

#ifdef OPERATION_2AXISTABLE_H
namespace OperationArchitecture
{
	AbstractOperation *Operation_2AxisTableCreate(const void *config, size_t &sizeOut)
	{
		const Operation_2AxisTableConfig *tableConfig = Config::CastConfigAndOffset<Operation_2AxisTableConfig>(config, sizeOut);

		switch(tableConfig->TableType)
		{
			case VariableType::UINT8:
				return new Operation_2AxisTable<uint8_t>(tableConfig);;
			case VariableType::UINT16:
				return new Operation_2AxisTable<uint16_t>(tableConfig);;
			case VariableType::UINT32:
				return new Operation_2AxisTable<uint32_t>(tableConfig);;
			case VariableType::UINT64:
				return new Operation_2AxisTable<uint64_t>(tableConfig);;
			case VariableType::INT8:
				return new Operation_2AxisTable<int8_t>(tableConfig);;
			case VariableType::INT16:
				return new Operation_2AxisTable<int16_t>(tableConfig);;
			case VariableType::INT32:
				return new Operation_2AxisTable<int32_t>(tableConfig);;
			case VariableType::INT64:
				return new Operation_2AxisTable<int64_t>(tableConfig);;
			case VariableType::FLOAT:
				return new Operation_2AxisTable<float>(tableConfig);;
			case VariableType::DOUBLE:
				return new Operation_2AxisTable<double>(tableConfig);;
			case VariableType::BOOLEAN:
				return new Operation_2AxisTable<bool>(tableConfig);;
			default:
				//should throw here
				return 0;
		}
	}
}
#endif