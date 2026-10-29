#include "Operations/Operation.h"
#include "Interpolation.h"
#include "Variable.h"

#ifndef OPERATION_MATH_H
#define OPERATION_MATH_H
namespace OperationArchitecture
{
	class Operation_Add : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Subtract : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Multiply : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Divide : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_And : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Or : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_GreaterThan : public AbstractOperation
	{
	public:	
		void AbstractExecute(Variable **params) override;
	};

	class Operation_LessThan : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Equal : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_GreaterThanOrEqual : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_LessThanOrEqual : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_Not : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};

	class Operation_NotEqual : public AbstractOperation
	{
	public:		
		void AbstractExecute(Variable **params) override;
	};
}
#endif