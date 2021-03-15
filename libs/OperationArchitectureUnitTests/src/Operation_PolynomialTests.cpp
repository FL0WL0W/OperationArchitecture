#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Polynomial.h"
using ::testing::AtLeast;
using ::testing::Return;

using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_PolynomialTest : public ::testing::Test 
	{
		protected:
		Operation_PolynomialConfig *_config;
		IOperation<Variable, Variable> *_operation;
		unsigned int _size = 0;

		Operation_PolynomialTest() 
		{			
			unsigned int expectedSize = sizeof(Operation_PolynomialConfig) + 4 * 4;
			_config = (Operation_PolynomialConfig *)malloc(expectedSize);
			
			((float *)(_config + 1))[0] = -10;
			((float *)(_config + 1))[1] = 10;
			((float *)(_config + 1))[2] = 10;
			((float *)(_config + 1))[3] = 10;
			((float *)(_config + 1))[4] = 0;
			_config->MaxValue = 150;
			_config->MinValue = -40;
			_config->Degree = 4;

			_operation = static_cast<IOperation<Variable, Variable> *>(Operation_Polynomial::Create(_config, _size));
		}
	};

	TEST_F(Operation_PolynomialTest, ConfigsAreCorrect)
	{
		ASSERT_EQ(29, _config->Size());
		//ASSERT_EQ(31, _size);
	}

	TEST_F(Operation_PolynomialTest, WhenGettingValueWithinLimits_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(-10, _operation->Execute(Variable::Create(0.0f)).To<float>());

		ASSERT_FLOAT_EQ(20, _operation->Execute(Variable::Create(1.0f)).To<float>());

		ASSERT_FLOAT_EQ(-1.25f, _operation->Execute(Variable::Create(0.5f)).To<float>());
	}

	TEST_F(Operation_PolynomialTest, WhenGettingValueAboveMaxValue_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(150, _operation->Execute(Variable::Create(100.0f)).To<float>());
	}

	TEST_F(Operation_PolynomialTest, WhenGettingValueBelowMinValue_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(-40, _operation->Execute(Variable::Create(-100.0f)).To<float>());
	}
}
