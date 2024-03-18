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
		AbstractOperation *_operationAdd;
		AbstractOperation *_operationSubtract;
		AbstractOperation *_operation;

		Operation_GroupTests() 
		{
			_operationAdd = new Operation_Add();
			_operationSubtract = new Operation_Subtract();
			AbstractOperation **operations = new AbstractOperation*[2];
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
		*variables[2] = 5;
		*variables[3] = 2;
		_operation->AbstractExecute(variables);

		ASSERT_EQ(*variables[0], 7);
		ASSERT_EQ(*variables[1], 3);
	}
}
