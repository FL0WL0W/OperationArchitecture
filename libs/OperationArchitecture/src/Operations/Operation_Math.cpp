#include "Operations/Operation_Math.h"
#include "Config.h"

#ifdef OPERATION_MATH_H
namespace OperationArchitecture
{
	Operation_Math::Operation_Math(const MathOperation operation)
	{
        NumberOfParameters = 2;
        ReturnsVariable = true;
		_operation = operation;
	}


	void Operation_Math::AbstractExecute(Variable &ret, Variable *params)
	{
		switch (_operation)
		{
			case ADD:
				ret.Set(params[0] + params[1]);
				break;
			case SUBTRACT:
				ret.Set(params[0] - params[1]);
				break;
			case MULTIPLY:
				ret.Set(params[0] * params[1]);
				break;
			case DIVIDE:
				ret.Set(params[0] / params[1]);
				break;
			case AND:
				ret.Set(params[0] & params[1]);
				break;
			case OR:
				ret.Set(params[0] | params[1]);
				break;
			case GREATERTHAN:
				ret.Set(params[0] > params[1]);
				break;
			case LESSTHAN:
				ret.Set(params[0] < params[1]);
				break;
			case GREATERTHANOREQUAL:
				ret.Set(params[0] >= params[1]);
				break;
			case EQUAL:
				ret.Set(params[0] == params[1]);
				break;
			case LESSTHANOREQUAL:
				ret.Set(params[0] <= params[1]);
				break;
		}
	}

	IOperationBase * Operation_Math::Create(const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		return new Operation_Math(Config::CastAndOffset<MathOperation>(config, sizeOut));
	}
}
#endif