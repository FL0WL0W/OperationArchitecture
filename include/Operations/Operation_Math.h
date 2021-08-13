#include "Operations/IOperation.h"
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

	class Operation_Add : public IOperationBase
	{
	public:		
		Operation_Add();

		void AbstractExecute(Variable **params) override;

		static Operation_Add Instance;
	};

	class Operation_Subtract : public IOperationBase
	{
	public:		
		Operation_Subtract();

		void AbstractExecute(Variable **params) override;

		static Operation_Subtract Instance;
	};

	class Operation_Multiply : public IOperationBase
	{
	public:		
		Operation_Multiply();

		void AbstractExecute(Variable **params) override;

		static Operation_Multiply Instance;
	};

	class Operation_Divide : public IOperationBase
	{
	public:		
		Operation_Divide();

		void AbstractExecute(Variable **params) override;

		static Operation_Divide Instance;
	};

	class Operation_And : public IOperationBase
	{
	public:		
		Operation_And();
		
		void AbstractExecute(Variable **params) override;

		static Operation_And Instance;
	};

	class Operation_Or : public IOperationBase
	{
	public:		
		Operation_Or();

		void AbstractExecute(Variable **params) override;

		static Operation_Or Instance;
	};

	class Operation_GreaterThan : public IOperationBase
	{
	public:	
		Operation_GreaterThan();

		void AbstractExecute(Variable **params) override;

		static Operation_GreaterThan Instance;
	};

	class Operation_LessThan : public IOperationBase
	{
	public:		
		Operation_LessThan();

		void AbstractExecute(Variable **params) override;

		static Operation_LessThan Instance;
	};

	class Operation_Equal : public IOperationBase
	{
	public:		
		Operation_Equal();

		void AbstractExecute(Variable **params) override;

		static Operation_Equal Instance;
	};

	class Operation_GreaterThanOrEqual : public IOperationBase
	{
	public:		
		Operation_GreaterThanOrEqual();

		void AbstractExecute(Variable **params) override;

		static Operation_GreaterThanOrEqual Instance;
	};

	class Operation_LessThanOrEqual : public IOperationBase
	{
	public:		
		Operation_LessThanOrEqual();

		void AbstractExecute(Variable **params) override;

		static Operation_LessThanOrEqual Instance;
	};
}
#endif