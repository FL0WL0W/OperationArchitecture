#include "Operations/Operation_Math.h"
#include "Config.h"

#ifdef OPERATION_MATH_H
namespace OperationArchitecture
{
	Operation_Math::Operation_Math(const MathOperation operation)
	{
		_operation = operation;
	}

	Variable Operation_Math::Execute(Variable x, Variable y)
	{
		switch (_operation)
		{
			case ADD:
				return x + y;
			case SUBTRACT:
				return x - y;
			case MULTIPLY:
				return x * y;
			case DIVIDE:
				return x / y;
			case AND:
				return x & y;
			case OR:
				return x | y;
			case GREATERTHAN:
				return Variable::Create((x > y));
			case LESSTHAN:
				return Variable::Create((x < y));
			case GREATERTHANOREQUAL:
				return Variable::Create((x >= y));
			case EQUAL:
				return Variable::Create((x == y));
			case LESSTHANOREQUAL:
				return Variable::Create((x <= y));
		}
		return Variable();
	}

	IOperationBase * Operation_Math::Create(const void *config, unsigned int &sizeOut)
	{
		Config::OffsetConfig(config, sizeOut, sizeof(uint32_t)); //skip over FactoryID
		return new Operation_Math(Config::CastAndOffset<MathOperation>(config, sizeOut));
	}
}
#endif