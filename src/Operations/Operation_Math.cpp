#include "Operations/Operation_Math.h"
#include "Config.h"

#ifdef OPERATION_MATH_H
namespace OperationArchitecture
{
	Operation_Add::Operation_Add() : IOperationBase(1, 2) { }
	void Operation_Add::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] + *variables[2]); }
	

	Operation_Subtract::Operation_Subtract() : IOperationBase(1, 2) { }
	void Operation_Subtract::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] - *variables[2]); }
	

	Operation_Multiply::Operation_Multiply() : IOperationBase(1, 2) { }
	void Operation_Multiply::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] * *variables[2]); }
	

	Operation_Divide::Operation_Divide() : IOperationBase(1, 2) { }
	void Operation_Divide::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] / *variables[2]); }
	

	Operation_And::Operation_And() : IOperationBase(1, 2) { }
	void Operation_And::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] & *variables[2]); }
	

	Operation_Or::Operation_Or() : IOperationBase(1, 2) { }
	void Operation_Or::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] | *variables[2]); }
	

	Operation_GreaterThan::Operation_GreaterThan() : IOperationBase(1, 2) { }
	void Operation_GreaterThan::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] > *variables[2]); }
	

	Operation_LessThan::Operation_LessThan() : IOperationBase(1, 2) { }
	void Operation_LessThan::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] < *variables[2]); }
	

	Operation_Equal::Operation_Equal() : IOperationBase(1, 2) { }
	void Operation_Equal::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] == *variables[2]); }
	

	Operation_GreaterThanOrEqual::Operation_GreaterThanOrEqual() : IOperationBase(1, 2) { }
	void Operation_GreaterThanOrEqual::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] >= *variables[2]); }
	

	Operation_LessThanOrEqual::Operation_LessThanOrEqual() : IOperationBase(1, 2) { }
	void Operation_LessThanOrEqual::AbstractExecute(Variable **variables) { variables[0]->Set(*variables[1] <= *variables[2]); }
}
#endif