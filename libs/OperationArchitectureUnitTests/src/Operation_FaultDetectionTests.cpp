#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_FaultDetection.h"
using ::testing::AtLeast;
using ::testing::Return;

using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_FaultDetectionTests : public ::testing::Test 
	{
		protected:
		Operation_FaultDetectionConfig *_config;
		IOperationBase *_operation;
		unsigned int _size = 0;

		Operation_FaultDetectionTests() 
		{			
			unsigned int expectedSize = sizeof(Operation_FaultDetectionConfig);
			_config = (Operation_FaultDetectionConfig *)malloc(expectedSize);
			
			_config->MaxValue = 150;
			_config->MinValue = -40;
			_config->DefaultValue = 4;

			void *config = malloc(_config->Size() + 4);
			void *buildConfig = config;

			//Factory ID doesn't matter
			*((uint32_t *)buildConfig) = 1337;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			memcpy(buildConfig, _config, _config->Size());
			buildConfig = (void *)((uint8_t *)buildConfig + _config->Size());

			_operation = Operation_FaultDetection::Create(config, _size);
		}
	};

	TEST_F(Operation_FaultDetectionTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(12, _config->Size());
		ASSERT_EQ(16, _size);
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
