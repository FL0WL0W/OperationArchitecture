#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Math.h"
using ::testing::AtLeast;
using ::testing::Return;

using namespace OperationArchitecture;

namespace UnitTests
{
		// GREATERTHAN = 6,
		// LESSTHAN = 7,
		// EQUAL = 8,
		// GREATERTHANOREQUAL = 9,
		// LESSTHANOREQUAL = 10

	
	IOperationBase *CreateOperationMath(MathOperation operation, unsigned int &size)
	{
		void *config = malloc(sizeof(MathOperation) + 4);
		void *buildConfig = config;

		//Factory ID doesn't matter
		*((uint32_t *)buildConfig) = 1337;
		buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

		*((MathOperation *)buildConfig) = operation;
		buildConfig = (void *)((MathOperation *)buildConfig + 1);

		return Operation_Math::Create(config, size);
	}

	//actual math verification done in VariableTests, This is to verify the functionality of the Operation_Math Only
	class Operation_MathTests : public ::testing::Test 
	{
		protected:
		IOperationBase *_operationAdd;
		unsigned int _sizeAdd = 0;
		IOperationBase *_operationSubtract;
		unsigned int _sizeSubtract = 0;
		IOperationBase *_operationMultiply;
		unsigned int _sizeMultiply = 0;
		IOperationBase *_operationDivide;
		unsigned int _sizeDivide = 0;
		IOperationBase *_operationAnd;
		unsigned int _sizeAnd = 0;
		IOperationBase *_operationOr;
		unsigned int _sizeOr = 0;

		Operation_MathTests() 
		{
			_operationAdd = CreateOperationMath(ADD, _sizeAdd);
			_operationSubtract = CreateOperationMath(SUBTRACT, _sizeSubtract);
			_operationMultiply = CreateOperationMath(MULTIPLY, _sizeMultiply);
			_operationDivide = CreateOperationMath(DIVIDE, _sizeDivide);
			_operationAnd = CreateOperationMath(AND, _sizeAnd);
			_operationOr = CreateOperationMath(OR, _sizeOr);
		}
	};

	TEST_F(Operation_MathTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(5, _sizeAdd);
		ASSERT_EQ(5, _sizeSubtract);
		ASSERT_EQ(5, _sizeMultiply);
		ASSERT_EQ(5, _sizeDivide);
		ASSERT_EQ(5, _sizeAnd);
		ASSERT_EQ(5, _sizeOr);
	}

	TEST_F(Operation_MathTests, WhenAdding_OperationAdds)
	{
		ASSERT_EQ(7, _operationAdd->Execute<int>(5, 2));
		ASSERT_EQ(8, _operationAdd->Execute<int>(6, 2));
	}

	TEST_F(Operation_MathTests, WhenSubtracting_OperationSubtracts)
	{
		ASSERT_EQ(3, _operationSubtract->Execute<int>(5, 2));
	}

	TEST_F(Operation_MathTests, WhenMultiplying_OperationMultiplies)
	{
		ASSERT_EQ(10, _operationMultiply->Execute<int>(5, 2));
	}

	TEST_F(Operation_MathTests, WhenDividing_OperationDivides)
	{
		ASSERT_EQ(2, _operationDivide->Execute<int>(5, 2));
	}

	TEST_F(Operation_MathTests, WhenAnding_OperationAnds)
	{
		ASSERT_EQ(0, _operationAnd->Execute<int>(5, 2));
	}

	TEST_F(Operation_MathTests, WhenOring_OperationOrs)
	{
		ASSERT_EQ(7, _operationOr->Execute<int>(5, 2));
		ASSERT_EQ(6, _operationOr->Execute<int>(6, 2));
	}
}
