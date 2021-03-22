#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Package.h"
#include "Operations/Operation_Math.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_PackageTests : public ::testing::Test 
	{
		protected:
		IOperationBase *_operation;
		IOperationBase *_operationAdd;
		OperationOrVariable _operationOrVariable[2];
		Variable _variables[2];

		Operation_PackageTests() 
		{	
			_operationOrVariable[0] = OperationOrVariable(&_variables[0]);
			_operationOrVariable[1] = OperationOrVariable(&_variables[1]);
			_operationAdd = new Operation_Math(ADD);
			_operation = new Operation_Package(_operationAdd, 0, _operationOrVariable);
		}
	};

	TEST_F(Operation_PackageTests, WhenExecutingOperation_VariableIsStored)
	{
		_variables[0].Set(20);
		_variables[1].Set(2);
		ASSERT_EQ(22, _operation->Execute<int>());

		_variables[0].Set(5);
		_variables[1].Set(2);
		ASSERT_EQ(7, _operation->Execute<int>());
	}
}
