#include "Config.h"
#include "Operations/Operation_Math.h"

#ifdef OPERATION_MATH_H
namespace OperationArchitecture
{
	Operation_Math::Operation_Math(MathOperation operation)
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
				return Variable((x > y));
			case LESSTHAN:
				return Variable((x < y));
			case GREATERTHANOREQUAL:
				return Variable((x >= y));
			case EQUAL:
				return Variable((x == y));
			case LESSTHANOREQUAL:
				return Variable((x <= y));
		}
		return Variable(static_cast<uint8_t>(0));
	}

	IOperationBase * Operation_Math::Create(const void *config, unsigned int &sizeOut)
	{
		return new Operation_Math(Config::CastAndOffset<MathOperation>(config, sizeOut));
	}
}
#endif