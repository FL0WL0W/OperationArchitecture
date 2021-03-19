#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_StoreVariable.h"
#include "Operations/Operation_Math.h"
using ::testing::AtLeast;
using ::testing::Return;

using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_StoreVariableTests : public ::testing::Test 
	{
		protected:
		IOperationBase *_operation;
		IOperationBase *_operationAdd;
		Variable _variable;

		Operation_StoreVariableTests() 
		{	
			_variable.Set(0);
			_operationAdd = new Operation_Math(ADD);
			_operation = new Operation_StoreVariable(&_variable, _operationAdd);
		}
	};

	TEST_F(Operation_StoreVariableTests, WhenExecutingOperation_VariableIsStored)
	{
		ASSERT_EQ(0, _variable.To<int>());

		ASSERT_EQ(22, _operation->Execute<int>(20, 2));
		ASSERT_EQ(22, _variable.To<int>());

		ASSERT_EQ(7, _operation->Execute<int>(5, 2));
		ASSERT_EQ(7, _variable.To<int>());
	}
}
