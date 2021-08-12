#include "Operations/Operation.h"
#include "Interpolation.h"
#include "Variable.h"

#ifndef OPERATION_MATH_H
#define OPERATION_MATH_H
namespace OperationArchitecture
{
	enum MathOperation : uint8_t
	{
		ADD = 0,
		SUBTRACT = 1,
		MULTIPLY = 2,
		DIVIDE = 3,
		AND = 4,
		OR = 5,
		GREATERTHAN = 6,
		LESSTHAN = 7,
		EQUAL = 8,
		GREATERTHANOREQUAL = 9,
		LESSTHANOREQUAL = 10
	};

	class Operation_Math
	{
	public:		
        static Operation *Construct(const MathOperation op);
		static Operation *Create(const void *config, size_t &sizeOut);
	};
}
#endif