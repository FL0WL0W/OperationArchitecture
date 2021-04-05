#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_StoreVariables.h"
#include "Operations/Operation_Math.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_ExecuteTests : public Test
	{
		protected:
		IOperationBase *_operation;
		IOperationBase *_operationAdd;

		Operation_ExecuteTests() 
		{	
			_operationAdd = new Operation_Math(ADD);
			_operation = new Operation_StoreVariables(_operationAdd, 0, false);
		}
	};

	TEST_F(Operation_ExecuteTests, WhenExecutingOperation_NoErrors)
	{
		_operation->Execute(20, 2);
		_operation->Execute(5, 2);
	}
}
