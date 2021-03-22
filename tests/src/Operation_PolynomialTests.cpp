#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Polynomial.h"
using ::testing::AtLeast;
using ::testing::Return;

using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_PolynomialTests : public ::testing::Test 
	{
		protected:
		Operation_PolynomialConfig *_config;
		IOperationBase *_operation;
		unsigned int _size = 0;

		Operation_PolynomialTests() 
		{			
			unsigned int expectedSize = sizeof(Operation_PolynomialConfig) + sizeof(float) * 4;
			_config = (Operation_PolynomialConfig *)malloc(expectedSize);
			
			((float *)(_config + 1))[0] = -10;
			((float *)(_config + 1))[1] = 10;
			((float *)(_config + 1))[2] = 10;
			((float *)(_config + 1))[3] = 10;
			((float *)(_config + 1))[4] = 0;
			_config->MaxValue = 150;
			_config->MinValue = -40;
			_config->Degree = 4;

			void *config = malloc(_config->Size() + sizeof(uint32_t));
			void *buildConfig = config;

			//Factory ID doesn't matter
			*((uint32_t *)buildConfig) = 1337;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			memcpy(buildConfig, _config, _config->Size());
			buildConfig = (void *)((uint8_t *)buildConfig + _config->Size());

			_operation = Operation_Polynomial::Create(config, _size);
		}
	};

	TEST_F(Operation_PolynomialTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(29, _config->Size());
		ASSERT_EQ(33, _size);
	}

	TEST_F(Operation_PolynomialTests, WhenGettingValueWithinLimits_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(-10, _operation->Execute<float>(0.0f));

		ASSERT_FLOAT_EQ(20, _operation->Execute<float>(1.0f));

		ASSERT_FLOAT_EQ(-1.25f, _operation->Execute<float>(0.5f));
	}

	TEST_F(Operation_PolynomialTests, WhenGettingValueAboveMaxValue_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(150, _operation->Execute<float>(100.0f));
	}

	TEST_F(Operation_PolynomialTests, WhenGettingValueBelowMinValue_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(-40, _operation->Execute<float>(-100.0f));
	}
}
