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

	class Operation_Add : public AbstractOperation
	{
	public:		
		Operation_Add();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Subtract : public AbstractOperation
	{
	public:		
		Operation_Subtract();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Multiply : public AbstractOperation
	{
	public:		
		Operation_Multiply();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Divide : public AbstractOperation
	{
	public:		
		Operation_Divide();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_And : public AbstractOperation
	{
	public:		
		Operation_And();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Or : public AbstractOperation
	{
	public:		
		Operation_Or();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_GreaterThan : public AbstractOperation
	{
	public:	
		Operation_GreaterThan();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_LessThan : public AbstractOperation
	{
	public:		
		Operation_LessThan();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Equal : public AbstractOperation
	{
	public:		
		Operation_Equal();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_GreaterThanOrEqual : public AbstractOperation
	{
	public:		
		Operation_GreaterThanOrEqual();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_LessThanOrEqual : public AbstractOperation
	{
	public:		
		Operation_LessThanOrEqual();
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Not : public AbstractOperation
	{
	public:		
		Operation_Not();
		void AbstractExecute(Variable **params) override;
	};
}
#endif