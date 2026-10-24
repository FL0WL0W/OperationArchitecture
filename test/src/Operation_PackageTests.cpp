#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Package.h"
#include "Operations/Operation_Math.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_PackageTests : public Test
	{
		protected:
		AbstractOperation *_operation;
		AbstractOperation *_operationAdd;
		Variable ** _variables = new Variable*[3];

		Operation_PackageTests() 
		{	
			_variables[0] = new Variable();
			_variables[1] = new Variable();
			_variables[2] = 0;
			_operation = new Operation_Package(new Operation_Add(), _variables, 3);
		}
	};

	TEST_F(Operation_PackageTests, WhenExecutingOperation_VariableIsStored)
	{
		*_variables[1] = 20;
		_operation->Execute(2);
		ASSERT_EQ(*_variables[0], 22);

		*_variables[1] = 5;
		_operation->Execute(2);
		ASSERT_EQ(*_variables[0], 7);
	}
}
