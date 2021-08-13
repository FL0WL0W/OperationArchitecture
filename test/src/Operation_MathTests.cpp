#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Math.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{	
	TEST(Operation_MathTests, WhenAdding_OperationAdds)
	{
		ASSERT_EQ(7, Operation_Add::Instance.Execute<int>(5, 2));
		ASSERT_EQ(8, Operation_Add::Instance.Execute<int>(6, 2));
	}

	TEST(Operation_MathTests, WhenSubtracting_OperationSubtracts)
	{
		ASSERT_EQ(3, Operation_Subtract::Instance.Execute<int>(5, 2));
	}

	TEST(Operation_MathTests, WhenMultiplying_OperationMultiplies)
	{
		ASSERT_EQ(10, Operation_Multiply::Instance.Execute<int>(5, 2));
	}

	TEST(Operation_MathTests, WhenDividing_OperationDivides)
	{
		ASSERT_EQ(2, Operation_Divide::Instance.Execute<int>(5, 2));
	}

	TEST(Operation_MathTests, WhenAnding_OperationAnds)
	{
		ASSERT_EQ(0, Operation_And::Instance.Execute<int>(5, 2));
	}

	TEST(Operation_MathTests, WhenOring_OperationOrs)
	{
		ASSERT_EQ(7, Operation_Or::Instance.Execute<int>(5, 2));
		ASSERT_EQ(6, Operation_Or::Instance.Execute<int>(6, 2));
	}

	TEST(Operation_MathTests, WhenGreaterThan_OperationReturnsGreaterThan)
	{
		ASSERT_EQ(true,  Operation_GreaterThan::Instance.Execute<bool>(5, 2));
		ASSERT_EQ(false, Operation_GreaterThan::Instance.Execute<bool>(5, 5));
		ASSERT_EQ(false, Operation_GreaterThan::Instance.Execute<bool>(2, 5));
	}

	TEST(Operation_MathTests, WhenLessThan_OperationReturnsLessThan)
	{
		ASSERT_EQ(false, Operation_LessThan::Instance.Execute<bool>(5, 2));
		ASSERT_EQ(false, Operation_LessThan::Instance.Execute<bool>(5, 5));
		ASSERT_EQ(true,  Operation_LessThan::Instance.Execute<bool>(2, 5));
	}

	TEST(Operation_MathTests, WhenEqual_OperationReturnsEqual)
	{
		ASSERT_EQ(false, Operation_Equal::Instance.Execute<bool>(5, 2));
		ASSERT_EQ(true,  Operation_Equal::Instance.Execute<bool>(5, 5));
		ASSERT_EQ(false, Operation_Equal::Instance.Execute<bool>(2, 5));
	}

	TEST(Operation_MathTests, WhenGreaterThanOrEqual_OperationReturnsGreaterThanOrEqual)
	{
		ASSERT_EQ(true,  Operation_GreaterThanOrEqual::Instance.Execute<bool>(5, 2));
		ASSERT_EQ(true,  Operation_GreaterThanOrEqual::Instance.Execute<bool>(5, 5));
		ASSERT_EQ(false, Operation_GreaterThanOrEqual::Instance.Execute<bool>(2, 5));
	}

	TEST(Operation_MathTests, WhenLessThanOrEqual_OperationReturnsLessThanOrEqual)
	{
		ASSERT_EQ(false, Operation_LessThanOrEqual::Instance.Execute<bool>(5, 2));
		ASSERT_EQ(true,  Operation_LessThanOrEqual::Instance.Execute<bool>(5, 5));
		ASSERT_EQ(true,  Operation_LessThanOrEqual::Instance.Execute<bool>(2, 5));
	}
}