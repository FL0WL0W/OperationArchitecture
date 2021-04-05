#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_StoreVariables.h"
#include "Operations/Operation_Math.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_StoreVariablesTests : public Test
	{
		protected:
		IOperationBase *_operation;
		IOperationBase *_operationNoStore;
		IOperationBase *_operationNoReturn;
		IOperationBase *_operationNoReturnOrStore;
		IOperationBase *_operationAdd;
		Variable *_variables;

		Operation_StoreVariablesTests() 
		{	
			_variables = new Variable[1];
			_variables[0].Set(0);
			_operationAdd = new Operation_Math(ADD);
			_operation = new Operation_StoreVariables(_operationAdd, &_variables, true);
			_operationNoStore = new Operation_StoreVariables(_operationAdd, 0, true);
			_operationNoReturn = new Operation_StoreVariables(_operationAdd, &_variables, false);
			_operationNoReturnOrStore = new Operation_StoreVariables(_operationAdd, 0, false);
		}
	};

	TEST_F(Operation_StoreVariablesTests, WhenExecutingOperation_VariableIsStored)
	{
		ASSERT_EQ(0, _variables[0].To<int>());

		ASSERT_EQ(22, _operation->Execute<int>(20, 2));
		ASSERT_EQ(22, _variables[0].To<int>());

		ASSERT_EQ(7, _operation->Execute<int>(5, 2));
		ASSERT_EQ(7, _variables[0].To<int>());

		_operationNoReturn->Execute(5, 10);
		ASSERT_EQ(15, _variables[0].To<int>());
	}

	TEST_F(Operation_StoreVariablesTests, WhenExecutingOperation_NoErrors)
	{
		_variables[0].Set(15);
		ASSERT_EQ(7, _operationNoStore->Execute<int>(5, 2));
		ASSERT_EQ(15, _variables[0].To<int>());
		
		_operationNoReturnOrStore->Execute(20, 2);
		_operationNoReturnOrStore->Execute(5, 2);
	}
}
