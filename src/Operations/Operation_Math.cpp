#include "Operations/Operation_Math.h"
#include "Config.h"

#ifdef OPERATION_MATH_H
namespace OperationArchitecture
{
	Operation_Add::Operation_Add() : AbstractOperation(1, 2) { }
	void Operation_Add::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] + *variables[2]); }
	

	Operation_Subtract::Operation_Subtract() : AbstractOperation(1, 2) { }
	void Operation_Subtract::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] - *variables[2]); }
	

	Operation_Multiply::Operation_Multiply() : AbstractOperation(1, 2) { }
	void Operation_Multiply::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] * *variables[2]); }
	

	Operation_Divide::Operation_Divide() : AbstractOperation(1, 2) { }
	void Operation_Divide::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] / *variables[2]); }
	

	Operation_And::Operation_And() : AbstractOperation(1, 2) { }
	void Operation_And::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] & *variables[2]); }
	

	Operation_Or::Operation_Or() : AbstractOperation(1, 2) { }
	void Operation_Or::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] | *variables[2]); }
	

	Operation_GreaterThan::Operation_GreaterThan() : AbstractOperation(1, 2) { }
	void Operation_GreaterThan::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] > *variables[2]); }
	

	Operation_LessThan::Operation_LessThan() : AbstractOperation(1, 2) { }
	void Operation_LessThan::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] < *variables[2]); }
	

	Operation_Equal::Operation_Equal() : AbstractOperation(1, 2) { }
	void Operation_Equal::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] == *variables[2]); }
	

	Operation_GreaterThanOrEqual::Operation_GreaterThanOrEqual() : AbstractOperation(1, 2) { }
	void Operation_GreaterThanOrEqual::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] >= *variables[2]); }
	

	Operation_LessThanOrEqual::Operation_LessThanOrEqual() : AbstractOperation(1, 2) { }
	void Operation_LessThanOrEqual::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] <= *variables[2]); }


	Operation_Not::Operation_Not() : AbstractOperation(1, 1) { }
	void Operation_Not::AbstractExecute(Variable **variables) 
	{ 
            if(variables[1]->Type == UINT8)
                return variables[0]->Set(!variables[1]->To<uint8_t>());
            if(variables[1]->Type == UINT16)
                return variables[0]->Set(!variables[1]->To<uint16_t>());
            if(variables[1]->Type == UINT32)
                return variables[0]->Set(!variables[1]->To<uint32_t>());
            if(variables[1]->Type == UINT64)
                return variables[0]->Set(!variables[1]->To<uint64_t>());
            if(variables[1]->Type == INT8)
                return variables[0]->Set(!variables[1]->To<int8_t>());
            if(variables[1]->Type == INT16)
                return variables[0]->Set(!variables[1]->To<int16_t>());
            if(variables[1]->Type == INT32)
                return variables[0]->Set(!variables[1]->To<int32_t>());
            if(variables[1]->Type == INT64)
                return variables[0]->Set(!variables[1]->To<int64_t>());
            if(variables[1]->Type == FLOAT)
                return variables[0]->Set(!variables[1]->To<float>());
            if(variables[1]->Type == DOUBLE)
                return variables[0]->Set(!variables[1]->To<double>());
            if(variables[1]->Type == BOOLEAN)
                return variables[0]->Set(!variables[1]->To<bool>());
            variables[0]->Set(!true);
		}
}
#endif