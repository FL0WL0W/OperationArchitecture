#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Math.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{	
	TEST(Operation_MathTests, WhenAdding_OperationAdds)
	{
		ASSERT_EQ(7, new Operation_Add()->Execute<int>(5, 2));
		ASSERT_EQ(8, new Operation_Add()->Execute<int>(6, 2));
	}

	TEST(Operation_MathTests, WhenSubtracting_OperationSubtracts)
	{
		ASSERT_EQ(3, new Operation_Subtract()->Execute<int>(5, 2));
	}

	TEST(Operation_MathTests, WhenMultiplying_OperationMultiplies)
	{
		ASSERT_EQ(10, new Operation_Multiply()->Execute<int>(5, 2));
	}

	TEST(Operation_MathTests, WhenDividing_OperationDivides)
	{
		ASSERT_EQ(2, new Operation_Divide()->Execute<int>(5, 2));
	}

	TEST(Operation_MathTests, WhenAnding_OperationAnds)
	{
		ASSERT_EQ(0, new Operation_And()->Execute<int>(5, 2));
	}

	TEST(Operation_MathTests, WhenOring_OperationOrs)
	{
		ASSERT_EQ(7, new Operation_Or()->Execute<int>(5, 2));
		ASSERT_EQ(6, new Operation_Or()->Execute<int>(6, 2));
	}

	TEST(Operation_MathTests, WhenGreaterThan_OperationReturnsGreaterThan)
	{
		ASSERT_EQ(true,  new Operation_GreaterThan()->Execute<bool>(5, 2));
		ASSERT_EQ(false, new Operation_GreaterThan()->Execute<bool>(5, 5));
		ASSERT_EQ(false, new Operation_GreaterThan()->Execute<bool>(2, 5));
	}

	TEST(Operation_MathTests, WhenLessThan_OperationReturnsLessThan)
	{
		ASSERT_EQ(false, new Operation_LessThan()->Execute<bool>(5, 2));
		ASSERT_EQ(false, new Operation_LessThan()->Execute<bool>(5, 5));
		ASSERT_EQ(true,  new Operation_LessThan()->Execute<bool>(2, 5));
	}

	TEST(Operation_MathTests, WhenEqual_OperationReturnsEqual)
	{
		ASSERT_EQ(false, new Operation_Equal()->Execute<bool>(5, 2));
		ASSERT_EQ(true,  new Operation_Equal()->Execute<bool>(5, 5));
		ASSERT_EQ(false, new Operation_Equal()->Execute<bool>(2, 5));
	}

	TEST(Operation_MathTests, WhenGreaterThanOrEqual_OperationReturnsGreaterThanOrEqual)
	{
		ASSERT_EQ(true,  new Operation_GreaterThanOrEqual()->Execute<bool>(5, 2));
		ASSERT_EQ(true,  new Operation_GreaterThanOrEqual()->Execute<bool>(5, 5));
		ASSERT_EQ(false, new Operation_GreaterThanOrEqual()->Execute<bool>(2, 5));
	}

	TEST(Operation_MathTests, WhenLessThanOrEqual_OperationReturnsLessThanOrEqual)
	{
		ASSERT_EQ(false, new Operation_LessThanOrEqual()->Execute<bool>(5, 2));
		ASSERT_EQ(true,  new Operation_LessThanOrEqual()->Execute<bool>(5, 5));
		ASSERT_EQ(true,  new Operation_LessThanOrEqual()->Execute<bool>(2, 5));
	}
}