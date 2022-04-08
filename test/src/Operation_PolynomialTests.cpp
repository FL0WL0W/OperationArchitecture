#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_Polynomial.h"
#include "Config.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_PolynomialTests : public Test
	{
		protected:
		Operation_PolynomialConfig<float> *_config;
		IOperationBase *_operation;
		size_t _size = 0;

		Operation_PolynomialTests() 
		{			
			size_t expectedSize = sizeof(Operation_PolynomialConfig<float>) + 
				((sizeof(Operation_PolynomialConfig<float>) % alignof(float) > 0)? (alignof(float) - (sizeof(Operation_PolynomialConfig<float>) % alignof(float))) : 0) + 
				sizeof(float) * 4;
			_config = (Operation_PolynomialConfig<float> *)malloc(expectedSize);
			
			_config->MaxValue = 150;
			_config->MinValue = -40;
			_config->Degree = 4;
			void* config = _config;
			size_t size = 0;
			Config::OffsetConfig(config, size, sizeof(Operation_PolynomialConfig<float>));
			Config::AlignConfig(config, size, alignof(float));
			float * Table = reinterpret_cast<float *>(config);
			Table[0] = -10;
			Table[1] = 10;
			Table[2] = 10;
			Table[3] = 10;
			Table[4] = 0;

			_operation = Operation_Polynomial<float>::Create(_config, _size);
		}
	};

	TEST_F(Operation_PolynomialTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(28, _config->Size());
		ASSERT_EQ(28, _size);
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
