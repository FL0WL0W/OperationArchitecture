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
		Operation *_operation;
		Operation *_operationAdd;
		OperationOrVariable _operationOrVariable[2];
		Variable _variables[2];

		Operation_PackageTests() 
		{	
			_operationOrVariable[0] = OperationOrVariable(&_variables[0]);
			_operationOrVariable[1] = OperationOrVariable(&_variables[1]);
			_operationAdd = Operation_Math::Construct(ADD);
			Operation_Package *operation_Package = new Operation_Package(_operationAdd, 0, _operationOrVariable);
			_operation = new Operation([operation_Package](Variable **variables) { operation_Package->Execute(variables); }, 1, 0);
			_operation->Destructor = [operation_Package]() { delete operation_Package; };
		}
	};

	TEST_F(Operation_PackageTests, WhenExecutingOperation_VariableIsStored)
	{
		_variables[0].Set(20);
		_variables[1].Set(2);
		ASSERT_EQ(22, _operation->ExecuteT<int>());

		_variables[0].Set(5);
		_variables[1].Set(2);
		ASSERT_EQ(7, _operation->ExecuteT<int>());
	}
}
