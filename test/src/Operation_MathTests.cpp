#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Math.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{	

	//actual math verification done in VariableTests, This is to verify the functionality of the Operation_Math Only
	class Operation_MathTests : public Test
	{
		protected:

		IOperationBase *CreateOperationMath(MathOperation operation, size_t &size)
		{
			void *config = malloc(sizeof(MathOperation));
			*reinterpret_cast<MathOperation *>(config) = operation;

			return Operation_Math::Create(config, size);
		}

		IOperationBase *_operationAdd;
		size_t _sizeAdd = 0;
		IOperationBase *_operationSubtract;
		size_t _sizeSubtract = 0;
		IOperationBase *_operationMultiply;
		size_t _sizeMultiply = 0;
		IOperationBase *_operationDivide;
		size_t _sizeDivide = 0;
		IOperationBase *_operationAnd;
		size_t _sizeAnd = 0;
		IOperationBase *_operationOr;
		size_t _sizeOr = 0;
		IOperationBase *_operationGreaterThan;
		size_t _sizeGreaterThan = 0;
		IOperationBase *_operationLessThan;
		size_t _sizeLessThan = 0;
		IOperationBase *_operationEqual;
		size_t _sizeEqual = 0;
		IOperationBase *_operationGreaterThanOrEqual;
		size_t _sizeGreaterThanOrEqual = 0;
		IOperationBase *_operationLessThanOrEqual;
		size_t _sizeLessThanOrEqual = 0;

		Operation_MathTests() 
		{
			_operationAdd = CreateOperationMath(ADD, _sizeAdd);
			_operationSubtract = CreateOperationMath(SUBTRACT, _sizeSubtract);
			_operationMultiply = CreateOperationMath(MULTIPLY, _sizeMultiply);
			_operationDivide = CreateOperationMath(DIVIDE, _sizeDivide);
			_operationAnd = CreateOperationMath(AND, _sizeAnd);
			_operationOr = CreateOperationMath(OR, _sizeOr);
			_operationGreaterThan = CreateOperationMath(GREATERTHAN, _sizeGreaterThan);
			_operationLessThan = CreateOperationMath(LESSTHAN, _sizeLessThan);
			_operationEqual = CreateOperationMath(EQUAL, _sizeEqual);
			_operationGreaterThanOrEqual = CreateOperationMath(GREATERTHANOREQUAL, _sizeGreaterThanOrEqual);
			_operationLessThanOrEqual = CreateOperationMath(LESSTHANOREQUAL, _sizeLessThanOrEqual);
		}
	};

	TEST_F(Operation_MathTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(1, _sizeAdd);
		ASSERT_EQ(1, _sizeSubtract);
		ASSERT_EQ(1, _sizeMultiply);
		ASSERT_EQ(1, _sizeDivide);
		ASSERT_EQ(1, _sizeAnd);
		ASSERT_EQ(1, _sizeOr);
		ASSERT_EQ(1, _sizeGreaterThan);
		ASSERT_EQ(1, _sizeLessThan);
		ASSERT_EQ(1, _sizeEqual);
		ASSERT_EQ(1, _sizeGreaterThanOrEqual);
		ASSERT_EQ(1, _sizeLessThanOrEqual);
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

	TEST_F(Operation_MathTests, WhenGreaterThan_OperationReturnsGreaterThan)
	{
		ASSERT_EQ(true, _operationGreaterThan->Execute<bool>(5, 2));
		ASSERT_EQ(false, _operationGreaterThan->Execute<bool>(5, 5));
		ASSERT_EQ(false, _operationGreaterThan->Execute<bool>(2, 5));
	}

	TEST_F(Operation_MathTests, WhenLessThan_OperationReturnsLessThan)
	{
		ASSERT_EQ(false, _operationLessThan->Execute<bool>(5, 2));
		ASSERT_EQ(false, _operationLessThan->Execute<bool>(5, 5));
		ASSERT_EQ(true, _operationLessThan->Execute<bool>(2, 5));
	}

	TEST_F(Operation_MathTests, WhenEqual_OperationReturnsEqual)
	{
		ASSERT_EQ(false, _operationEqual->Execute<bool>(5, 2));
		ASSERT_EQ(true, _operationEqual->Execute<bool>(5, 5));
		ASSERT_EQ(false, _operationEqual->Execute<bool>(2, 5));
	}

	TEST_F(Operation_MathTests, WhenGreaterThanOrEqual_OperationReturnsGreaterThanOrEqual)
	{
		ASSERT_EQ(true, _operationGreaterThanOrEqual->Execute<bool>(5, 2));
		ASSERT_EQ(true, _operationGreaterThanOrEqual->Execute<bool>(5, 5));
		ASSERT_EQ(false, _operationGreaterThanOrEqual->Execute<bool>(2, 5));
	}

	TEST_F(Operation_MathTests, WhenLessThanOrEqual_OperationReturnsLessThanOrEqual)
	{
		ASSERT_EQ(false, _operationLessThanOrEqual->Execute<bool>(5, 2));
		ASSERT_EQ(true, _operationLessThanOrEqual->Execute<bool>(5, 5));
		ASSERT_EQ(true, _operationLessThanOrEqual->Execute<bool>(2, 5));
	}
}