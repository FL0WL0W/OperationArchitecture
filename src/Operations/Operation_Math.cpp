#include "Operations/Operation_Math.h"
#include "Config.h"

#ifdef OPERATION_MATH_H
namespace OperationArchitecture
{
	Operation *Operation_Math::Construct(const MathOperation op)
	{
		switch (op)
		{
			case ADD:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] + *variables[2]); }, 1, 2);
			case SUBTRACT:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] - *variables[2]); }, 1, 2);
			case MULTIPLY:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] * *variables[2]); }, 1, 2);
			case DIVIDE:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] / *variables[2]); }, 1, 2);
			case AND:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] & *variables[2]); }, 1, 2);
			case OR:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] | *variables[2]); }, 1, 2);
			case GREATERTHAN:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] > *variables[2]); }, 1, 2);
			case LESSTHAN:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] < *variables[2]); }, 1, 2);
			case GREATERTHANOREQUAL:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] >= *variables[2]); }, 1, 2);
			case EQUAL:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] == *variables[2]); }, 1, 2);
			case LESSTHANOREQUAL:
				return new Operation([](Variable **variables) { variables[0]->Set(*variables[1] <= *variables[2]); }, 1, 2);
		}
	}

	Operation * Operation_Math::Create(const void *config, size_t &sizeOut)
	{
		const MathOperation op = Config::CastAndOffset<MathOperation>(config, sizeOut);
		return Construct(op);
	}
}
#endif