#include "Config.h"
#include "Operations/Operation_StaticScalar.h"

#ifdef OPERATION_STATICSCALAR_H
namespace OperationArchitecture
{
	Operation_StaticScalar::Operation_StaticScalar(const Variable &staticValue)
	{
		_staticValue = staticValue;
	}

	Variable Operation_StaticScalar::Execute()
	{
		return _staticValue;
	}

	IOperationBase * Operation_StaticScalar::Create(const void *config, unsigned int &sizeOut)
	{
		const VariableType staticValueType = Config::CastAndOffset<VariableType>(config, sizeOut);
		Variable staticValue;
		switch (staticValueType)
		{
			case VariableType::UINT8:
				staticValue = Variable::Create(Config::CastAndOffset<uint8_t>(config, sizeOut));
				break;
			case VariableType::UINT16:
				staticValue = Variable::Create(Config::CastAndOffset<uint16_t>(config, sizeOut));
				break;
			case VariableType::UINT32:
				staticValue = Variable::Create(Config::CastAndOffset<uint32_t>(config, sizeOut));
				break;
			case VariableType::UINT64:
				staticValue = Variable::Create(Config::CastAndOffset<uint64_t>(config, sizeOut));
				break;
			case VariableType::INT8:
				staticValue = Variable::Create(Config::CastAndOffset<int8_t>(config, sizeOut));
				break;
			case VariableType::INT16:
				staticValue = Variable::Create(Config::CastAndOffset<int16_t>(config, sizeOut));
				break;
			case VariableType::INT32:
				staticValue = Variable::Create(Config::CastAndOffset<int32_t>(config, sizeOut));
				break;
			case VariableType::INT64:
				staticValue = Variable::Create(Config::CastAndOffset<int64_t>(config, sizeOut));
				break;
			case VariableType::FLOAT:
				staticValue = Variable::Create(Config::CastAndOffset<float>(config, sizeOut));
				break;
			case VariableType::DOUBLE:
				staticValue = Variable::Create(Config::CastAndOffset<double>(config, sizeOut));
				break;
			case VariableType::BOOLEAN:
				staticValue = Variable::Create(Config::CastAndOffset<bool>(config, sizeOut));
				break;
			case VariableType::VOID: 
				staticValue = Variable();
				//this would be useless to create
				break;
		}
		
		Operation_StaticScalar *variableService = new Operation_StaticScalar(staticValue);

		return variableService;
	}
}
#endif