#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Math.h"
#include "Operations/Operation_Group.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{	
	class Operation_GroupTests : public Test
	{
		protected:
		IOperationBase *_operationAdd;
		IOperationBase *_operationSubtract;
		IOperationBase *_operation;

		Operation_GroupTests() 
		{
			size_t size = 0;
			_operationAdd = &Operation_Add::Instance;
			_operationSubtract = &Operation_Subtract::Instance;
			IOperationBase **operations = new IOperationBase*[2];
			operations[0] = _operationAdd;
			operations[1] = _operationSubtract;
			_operation = new Operation_Group(operations, 2);
		}
	};

	TEST_F(Operation_GroupTests, WhenExecuting_OperationAddsAndSubtracts)
	{
		ASSERT_EQ(7, _operationAdd->Execute<int>(5, 2));
		ASSERT_EQ(3, _operationSubtract->Execute<int>(5, 2));

		Variable **variables = new Variable*[4];
		for(int i = 0; i < 4; i++)
			variables[i] = new Variable();
		variables[2]->Set(5);
		variables[3]->Set(2);
		_operation->AbstractExecute(variables);

		ASSERT_EQ(7, variables[0]->To<int>());
		ASSERT_EQ(3, variables[1]->To<int>());
	}
}
