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
		IOperationBase *_operation;
		IOperationBase *_operationAdd;
		Variable ** _variables = new Variable*[3];

		Operation_PackageTests() 
		{	
			_variables[0] = new Variable(0);
			_variables[1] = new Variable(0);
			_variables[2] = new Variable(0);
			_operation = new Operation_Package(new Operation_Add(), _variables);
		}
	};

	TEST_F(Operation_PackageTests, WhenExecutingOperation_VariableIsStored)
	{
		_variables[1]->Set(20);
		_variables[2]->Set(2);
		_operation->Execute();
		ASSERT_EQ(22, _variables[0]->To<int>());

		_variables[1]->Set(5);
		_variables[2]->Set(2);
		_operation->Execute();
		ASSERT_EQ(7, _variables[0]->To<int>());
	}
}
