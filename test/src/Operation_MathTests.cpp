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

		Operation *CreateOperationMath(MathOperation operation, size_t &size)
		{
			void *config = malloc(sizeof(MathOperation));
			*reinterpret_cast<MathOperation *>(config) = operation;

			return Operation_Math::Create(config, size);
		}

		Operation *_operationAdd;
		size_t _sizeAdd = 0;
		Operation *_operationSubtract;
		size_t _sizeSubtract = 0;
		Operation *_operationMultiply;
		size_t _sizeMultiply = 0;
		Operation *_operationDivide;
		size_t _sizeDivide = 0;
		Operation *_operationAnd;
		size_t _sizeAnd = 0;
		Operation *_operationOr;
		size_t _sizeOr = 0;
		Operation *_operationGreaterThan;
		size_t _sizeGreaterThan = 0;
		Operation *_operationLessThan;
		size_t _sizeLessThan = 0;
		Operation *_operationEqual;
		size_t _sizeEqual = 0;
		Operation *_operationGreaterThanOrEqual;
		size_t _sizeGreaterThanOrEqual = 0;
		Operation *_operationLessThanOrEqual;
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
		ASSERT_EQ(7, _operationAdd->ExecuteT<int>(5, 2));
		ASSERT_EQ(8, _operationAdd->ExecuteT<int>(6, 2));
	}

	TEST_F(Operation_MathTests, WhenSubtracting_OperationSubtracts)
	{
		ASSERT_EQ(3, _operationSubtract->ExecuteT<int>(5, 2));
	}

	TEST_F(Operation_MathTests, WhenMultiplying_OperationMultiplies)
	{
		ASSERT_EQ(10, _operationMultiply->ExecuteT<int>(5, 2));
	}

	TEST_F(Operation_MathTests, WhenDividing_OperationDivides)
	{
		ASSERT_EQ(2, _operationDivide->ExecuteT<int>(5, 2));
	}

	TEST_F(Operation_MathTests, WhenAnding_OperationAnds)
	{
		ASSERT_EQ(0, _operationAnd->ExecuteT<int>(5, 2));
	}

	TEST_F(Operation_MathTests, WhenOring_OperationOrs)
	{
		ASSERT_EQ(7, _operationOr->ExecuteT<int>(5, 2));
		ASSERT_EQ(6, _operationOr->ExecuteT<int>(6, 2));
	}

	TEST_F(Operation_MathTests, WhenGreaterThan_OperationReturnsGreaterThan)
	{
		ASSERT_EQ(true, _operationGreaterThan->ExecuteT<bool>(5, 2));
		ASSERT_EQ(false, _operationGreaterThan->ExecuteT<bool>(5, 5));
		ASSERT_EQ(false, _operationGreaterThan->ExecuteT<bool>(2, 5));
	}

	TEST_F(Operation_MathTests, WhenLessThan_OperationReturnsLessThan)
	{
		ASSERT_EQ(false, _operationLessThan->ExecuteT<bool>(5, 2));
		ASSERT_EQ(false, _operationLessThan->ExecuteT<bool>(5, 5));
		ASSERT_EQ(true, _operationLessThan->ExecuteT<bool>(2, 5));
	}

	TEST_F(Operation_MathTests, WhenEqual_OperationReturnsEqual)
	{
		ASSERT_EQ(false, _operationEqual->ExecuteT<bool>(5, 2));
		ASSERT_EQ(true, _operationEqual->ExecuteT<bool>(5, 5));
		ASSERT_EQ(false, _operationEqual->ExecuteT<bool>(2, 5));
	}

	TEST_F(Operation_MathTests, WhenGreaterThanOrEqual_OperationReturnsGreaterThanOrEqual)
	{
		ASSERT_EQ(true, _operationGreaterThanOrEqual->ExecuteT<bool>(5, 2));
		ASSERT_EQ(true, _operationGreaterThanOrEqual->ExecuteT<bool>(5, 5));
		ASSERT_EQ(false, _operationGreaterThanOrEqual->ExecuteT<bool>(2, 5));
	}

	TEST_F(Operation_MathTests, WhenLessThanOrEqual_OperationReturnsLessThanOrEqual)
	{
		ASSERT_EQ(false, _operationLessThanOrEqual->ExecuteT<bool>(5, 2));
		ASSERT_EQ(true, _operationLessThanOrEqual->ExecuteT<bool>(5, 5));
		ASSERT_EQ(true, _operationLessThanOrEqual->ExecuteT<bool>(2, 5));
	}
}