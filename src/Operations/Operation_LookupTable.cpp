#include "Operations/Operation_LookupTable.h"

#ifdef OPERATION_LOOKUPTABLE_H
namespace OperationArchitecture
{

	IOperationBase *Operation_LookupTableCreate(const void *config, size_t &sizeOut)
	{
		const Operation_LookupTableConfig *tableConfig = Config::CastConfigAndOffset<Operation_LookupTableConfig>(config, sizeOut);

		switch(tableConfig->TableType)
		{
			case VariableType::UINT8:
				return new Operation_LookupTable<uint8_t>(tableConfig);
			case VariableType::UINT16:
				return new Operation_LookupTable<uint16_t>(tableConfig);
			case VariableType::UINT32:
				return new Operation_LookupTable<uint32_t>(tableConfig);
			case VariableType::UINT64:
				return new Operation_LookupTable<uint64_t>(tableConfig);
			case VariableType::INT8:
				return new Operation_LookupTable<int8_t>(tableConfig);
			case VariableType::INT16:
				return new Operation_LookupTable<int16_t>(tableConfig);
			case VariableType::INT32:
				return new Operation_LookupTable<int32_t>(tableConfig);
			case VariableType::INT64:
				return new Operation_LookupTable<int64_t>(tableConfig);
			case VariableType::FLOAT:
				return new Operation_LookupTable<float>(tableConfig);
			case VariableType::DOUBLE:
				return new Operation_LookupTable<double>(tableConfig);
			case VariableType::BOOLEAN:
				return new Operation_LookupTable<bool>(tableConfig);
			default:
				//should throw here
				return 0;
		}
	}
}
#endif