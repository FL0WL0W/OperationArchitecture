#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_LookupTable.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_LookupTableTests : public Test
	{
		protected:
		Operation_LookupTableConfig *_config;
		IOperationBase *_operation;
		unsigned int _size = 0;

		Operation_LookupTableTests() 
		{			
			unsigned int expectedSize = sizeof(Operation_LookupTableConfig) + 4 * 11;
			_config = (Operation_LookupTableConfig *)malloc(expectedSize);
			
			_config->MinXValue = 0;
			_config->MaxXValue = 3.3f;
			_config->XResolution = 11;
			_config->TableType = VariableType::FLOAT;
			float * Table = (float *)(_config + 1);
			Table[0] = -10;
			Table[1] = 0;
			Table[2] = 10;
			Table[3] = 20;
			Table[4] = 30;
			Table[5] = 40;
			Table[6] = 50;
			Table[7] = 60;
			Table[8] = 70;
			Table[9] = 80;
			Table[10] = 90;

			void *config = malloc(_config->Size() + sizeof(uint32_t));
			void *buildConfig = config;

			//Factory ID doesn't matter
			*((uint32_t *)buildConfig) = 1337;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			memcpy(buildConfig, _config, _config->Size());
			buildConfig = (void *)((uint8_t *)buildConfig + _config->Size());

			_operation = Operation_LookupTable::Create(config, _size);
		}
	};

	TEST_F(Operation_LookupTableTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(54, _config->Size());
		ASSERT_EQ(58, _size);
		ASSERT_EQ((float *)(_config + 1), _config->Table());
		ASSERT_EQ(-10, reinterpret_cast<const float*>(_config->Table())[0]);
	}

	TEST_F(Operation_LookupTableTests, WhenGettingValueInTable_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(-10, _operation->Execute<float>(0.0f));

		ASSERT_FLOAT_EQ(20, _operation->Execute<float>(0.99f));

		ASSERT_NEAR(0, _operation->Execute<float>(0.33f), 0.001f);

		ASSERT_NEAR(-1.25f, _operation->Execute<float>(0.28875f), 0.001f);
	}

	TEST_F(Operation_LookupTableTests, WhenGettingValueAboveMaxValue_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(90, _operation->Execute<float>(100.0f));
	}

	TEST_F(Operation_LookupTableTests, WhenGettingValueBelowMinValue_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(-10, _operation->Execute<float>(-1.0f));
	}
}
