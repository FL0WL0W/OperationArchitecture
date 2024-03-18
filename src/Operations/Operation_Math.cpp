#include "Operations/Operation_Math.h"
#include "Config.h"

#ifdef OPERATION_MATH_H
namespace OperationArchitecture
{
	Operation_Add::Operation_Add() : AbstractOperation(1, 2) { }
	void Operation_Add::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] + *variables[2]; }
	

	Operation_Subtract::Operation_Subtract() : AbstractOperation(1, 2) { }
	void Operation_Subtract::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] - *variables[2]; }
	

	Operation_Multiply::Operation_Multiply() : AbstractOperation(1, 2) { }
	void Operation_Multiply::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] * *variables[2]; }
	

	Operation_Divide::Operation_Divide() : AbstractOperation(1, 2) { }
	void Operation_Divide::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] / *variables[2]; }
	

	Operation_And::Operation_And() : AbstractOperation(1, 2) { }
	void Operation_And::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] & *variables[2]; }
	

	Operation_Or::Operation_Or() : AbstractOperation(1, 2) { }
	void Operation_Or::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] | *variables[2]; }
	

	Operation_GreaterThan::Operation_GreaterThan() : AbstractOperation(1, 2) { }
	void Operation_GreaterThan::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] > *variables[2]; }
	

	Operation_LessThan::Operation_LessThan() : AbstractOperation(1, 2) { }
	void Operation_LessThan::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] < *variables[2]; }
	

	Operation_Equal::Operation_Equal() : AbstractOperation(1, 2) { }
	void Operation_Equal::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] == *variables[2]; }
	

	Operation_GreaterThanOrEqual::Operation_GreaterThanOrEqual() : AbstractOperation(1, 2) { }
	void Operation_GreaterThanOrEqual::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] >= *variables[2]; }
	

	Operation_LessThanOrEqual::Operation_LessThanOrEqual() : AbstractOperation(1, 2) { }
	void Operation_LessThanOrEqual::AbstractExecute(Variable **variables) { *variables[0] = *variables[1] <= *variables[2]; }


	Operation_Not::Operation_Not() : AbstractOperation(1, 1) { }
	void Operation_Not::AbstractExecute(Variable **variables) 
	{ 
            if(variables[1]->Type == UINT8)
                *variables[0] = !static_cast<uint8_t>(*variables[1]);
            else if(variables[1]->Type == UINT16)
                *variables[0] = !static_cast<uint16_t>(*variables[1]);
            else if(variables[1]->Type == UINT32)
                *variables[0] = !static_cast<uint32_t>(*variables[1]);
            else if(variables[1]->Type == UINT64)
                *variables[0] = !static_cast<uint64_t>(*variables[1]);
            else if(variables[1]->Type == INT8)
                *variables[0] = !static_cast<int8_t>(*variables[1]);
            else if(variables[1]->Type == INT16)
                *variables[0] = !static_cast<int16_t>(*variables[1]);
            else if(variables[1]->Type == INT32)
                *variables[0] = !static_cast<int32_t>(*variables[1]);
            else if(variables[1]->Type == INT64)
                *variables[0] = !static_cast<int64_t>(*variables[1]);
            else if(variables[1]->Type == FLOAT)
                *variables[0] = !static_cast<float>(*variables[1]);
            else if(variables[1]->Type == DOUBLE)
                *variables[0] = !static_cast<double>(*variables[1]);
            else if(variables[1]->Type == BOOLEAN)
                *variables[0] = !static_cast<bool>(*variables[1]);
            else 
				*variables[0] = !true;
		}
}
#endif