#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_FaultDetection.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_FaultDetectionTests : public Test
	{
		protected:
		Operation_FaultDetectionConfig<float> *_config;
		IOperationBase *_operation;
		size_t _size = 0;

		Operation_FaultDetectionTests() 
		{			
			size_t expectedSize = sizeof(Operation_FaultDetectionConfig<float>);
			_config = (Operation_FaultDetectionConfig<float> *)malloc(expectedSize);
			
			_config->MaxValue = 150;
			_config->MinValue = -40;
			_config->DefaultValue = 4;

			_operation = Operation_FaultDetection<float>::Create(_config, _size);
		}
	};

	TEST_F(Operation_FaultDetectionTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(12, _config->Size());
		ASSERT_EQ(12, _size);
	}

	TEST_F(Operation_FaultDetectionTests, WhenGettingValueWithinLimits_ThenCorrectValueIsReturned)
	{
		ASSERT_EQ(20, _operation->Execute<int>(20));
		ASSERT_EQ(-40, _operation->Execute<int>(-40));
		ASSERT_EQ(150, _operation->Execute<int>(150));
	}

	TEST_F(Operation_FaultDetectionTests, WhenGettingValueAboveMaxValue_ThenCorrectValueIsReturned)
	{
		ASSERT_EQ(4, _operation->Execute<int>(151));
	}

	TEST_F(Operation_FaultDetectionTests, WhenGettingValueBelowMinValue_ThenCorrectValueIsReturned)
	{
		ASSERT_EQ(4, _operation->Execute<int>(-41));
	}
}
