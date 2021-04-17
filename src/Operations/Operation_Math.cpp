#include "Operations/Operation_Math.h"
#include "Config.h"

#ifdef OPERATION_MATH_H
namespace OperationArchitecture
{
	Operation_Math::Operation_Math(const MathOperation operation)
	{
		NumberOfReturnVariables = 1;
        NumberOfParameters = 2;
		_operation = operation;
	}


	void Operation_Math::AbstractExecute(Variable **variables)
	{
		switch (_operation)
		{
			case ADD:
				variables[0]->Set(*variables[1] + *variables[2]);
				break;
			case SUBTRACT:
				variables[0]->Set(*variables[1] - *variables[2]);
				break;
			case MULTIPLY:
				variables[0]->Set(*variables[1] * *variables[2]);
				break;
			case DIVIDE:
				variables[0]->Set(*variables[1] / *variables[2]);
				break;
			case AND:
				variables[0]->Set(*variables[1] & *variables[2]);
				break;
			case OR:
				variables[0]->Set(*variables[1] | *variables[2]);
				break;
			case GREATERTHAN:
				variables[0]->Set(*variables[1] > *variables[2]);
				break;
			case LESSTHAN:
				variables[0]->Set(*variables[1] < *variables[2]);
				break;
			case GREATERTHANOREQUAL:
				variables[0]->Set(*variables[1] >= *variables[2]);
				break;
			case EQUAL:
				variables[0]->Set(*variables[1] == *variables[2]);
				break;
			case LESSTHANOREQUAL:
				variables[0]->Set(*variables[1] <= *variables[2]);
				break;
		}
	}

	IOperationBase * Operation_Math::Create(const void *config, unsigned int &sizeOut)
	{
		return new Operation_Math(Config::CastAndOffset<MathOperation>(config, sizeOut));
	}
}
#endif