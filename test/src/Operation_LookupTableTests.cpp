#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_LookupTable.h"
#include "Config.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_LookupTableTests : public Test
	{
		protected:
		Operation_LookupTableConfig *_config;
		AbstractOperation *_operation;
		size_t _size = 0;

		Operation_LookupTableTests() 
		{			
			size_t expectedSize = sizeof(Operation_LookupTableConfig) + 
				((sizeof(Operation_LookupTableConfig) % alignof(float) > 0)? (alignof(float) - (sizeof(Operation_LookupTableConfig) % alignof(float))) : 0) + 
				sizeof(float) * 11 + 
				sizeof(float) * 11;
			_config = (Operation_LookupTableConfig *)malloc(expectedSize);
			
			_config->XResolution = 11;
			_config->TableType = VariableType::FLOAT;
			void* config = _config;
			size_t size = 0;
			Config::OffsetConfig(config, size, sizeof(Operation_LookupTableConfig));
			Config::AlignConfig(config, size, alignof(float));
			float * XAxis = reinterpret_cast<float *>(config);
			XAxis[0] = 0;
			XAxis[1] = 0.33f;
			XAxis[2] = 0.66f;
			XAxis[3] = 0.99f;
			XAxis[4] = 1.32f;
			XAxis[5] = 1.65f;
			XAxis[6] = 1.98f;
			XAxis[7] = 2.31f;
			XAxis[8] = 2.90f;
			XAxis[9] = 2.97f;
			XAxis[10] = 3.3f;
			Config::OffsetConfig(config, size, sizeof(float) * 11);
			float * Table = reinterpret_cast<float *>(config);
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

			_operation = Operation_LookupTableCreate(_config, _size);
		}
	};

	TEST_F(Operation_LookupTableTests, ConfigsAreCorrect)
	{
		void* config = _config;
		size_t size = 0;
		Config::OffsetConfig(config, size, sizeof(Operation_LookupTableConfig));
		Config::AlignConfig(config, size, alignof(float));
		ASSERT_EQ((float *)(config), _config->XAxis());
		Config::OffsetConfig(config, size, sizeof(float) * 11);
		ASSERT_EQ((float *)(config), _config->Table<float>());
		Config::OffsetConfig(config, size, sizeof(float) * 11);
		ASSERT_EQ(-10, reinterpret_cast<const float*>(_config->Table<float>())[0]);
		ASSERT_EQ(size, _config->Size());
		ASSERT_EQ(size, _size);
	}

	TEST_F(Operation_LookupTableTests, WhenGettingValueInTable_ThenCorrectValueIsReturned)
	{
		ASSERT_FLOAT_EQ(-10, _operation->Execute<float>(0.0f));

		ASSERT_FLOAT_EQ(20, _operation->Execute<float>(0.99f));

		ASSERT_NEAR(0, _operation->Execute<float>(0.33f), 0.001f);

		ASSERT_NEAR(60, _operation->Execute<float>(2.31f), 0.001f);

		ASSERT_NEAR(62.5, _operation->Execute<float>(2.4575f), 0.001f);

		ASSERT_NEAR(65, _operation->Execute<float>(2.605f), 0.001f);

		ASSERT_NEAR(67.5, _operation->Execute<float>(2.7525f), 0.001f);

		ASSERT_NEAR(70, _operation->Execute<float>(2.90f), 0.001f);

		ASSERT_NEAR(72.5, _operation->Execute<float>(2.9175f), 0.001f);

		ASSERT_NEAR(75, _operation->Execute<float>(2.935f), 0.001f);

		ASSERT_NEAR(77.5, _operation->Execute<float>(2.9525f), 0.001f);

		ASSERT_NEAR(80, _operation->Execute<float>(2.97f), 0.001f);

		ASSERT_NEAR(82.5, _operation->Execute<float>(3.0525f), 0.001f);

		ASSERT_NEAR(85, _operation->Execute<float>(3.135f), 0.001f);

		ASSERT_NEAR(87.5, _operation->Execute<float>(3.2175f), 0.001f);

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
