#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_2AxisTable.h"
#include "Config.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_2AxisTableTests : public Test
	{
		protected:
		Operation_2AxisTableConfig *_config;
		AbstractOperation *_operation;
		size_t _size = 0;

		Operation_2AxisTableTests() 
		{			
			_config = (Operation_2AxisTableConfig *)malloc(sizeof(Operation_2AxisTableConfig) + 
				((sizeof(Operation_2AxisTableConfig) % alignof(float) > 0)? (alignof(float) - (sizeof(Operation_2AxisTableConfig) % alignof(float))) : 0) + 
				sizeof(float) * 10 + 
				sizeof(float) * 4 + 
				sizeof(float) * 40);
			
			_config->XResolution = 10;
			_config->YResolution = 4;
			_config->TableType = VariableType::FLOAT;
			void* config = _config;
			size_t size = 0;
			Config::OffsetConfig(config, size, sizeof(Operation_2AxisTableConfig));
			Config::AlignConfig(config, size, alignof(float));
			float * XAxis = reinterpret_cast<float *>(config);
			Config::OffsetConfig(config, size, sizeof(float) * 10);
			XAxis[0] = 0;
			XAxis[1] = 0.33f;
			XAxis[2] = 0.66f;
			XAxis[3] = 0.99f;
			XAxis[4] = 1.32f;
			XAxis[5] = 1.65f;
			XAxis[6] = 1.98f;
			XAxis[7] = 2.31f;
			XAxis[8] = 2.64f;
			XAxis[9] = 2.97f;
			float * YAxis = reinterpret_cast<float *>(config);
			Config::OffsetConfig(config, size, sizeof(float) * 4);
			YAxis[0] = 0;
			YAxis[1] = 1.1f;
			YAxis[2] = 2.2f;
			YAxis[3] = 3.3f;
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
			Table[10] = 0;
			Table[11] = 10;
			Table[12] = 20;
			Table[13] = 30;
			Table[14] = 40;
			Table[15] = 50;
			Table[16] = 60;
			Table[17] = 70;
			Table[18] = 80;
			Table[19] = 90;
			Table[20] = 10;
			Table[21] = 20;
			Table[22] = 30;
			Table[23] = 40;
			Table[24] = 50;
			Table[25] = 60;
			Table[26] = 70;
			Table[27] = 80;
			Table[28] = 90;
			Table[29] = 100;
			Table[30] = 20;
			Table[31] = 30;
			Table[32] = 40;
			Table[33] = 50;
			Table[34] = 60;
			Table[35] = 70;
			Table[36] = 80;
			Table[37] = 90;
			Table[38] = 100;
			Table[39] = 110;

			_operation = Operation_2AxisTableCreate(_config, _size);
		}
	};

	TEST_F(Operation_2AxisTableTests, ConfigsAreCorrect)
	{
		void* config = _config;
		size_t size = 0;
		Config::OffsetConfig(config, size, sizeof(Operation_2AxisTableConfig));
		Config::AlignConfig(config, size, alignof(float));
		ASSERT_EQ((float *)(config), _config->XAxis());
		Config::OffsetConfig(config, size, sizeof(float) * 10);
		ASSERT_EQ((float *)(config), _config->YAxis());
		Config::OffsetConfig(config, size, sizeof(float) * 4);
		ASSERT_EQ((float *)(config), _config->Table<float>());
		ASSERT_EQ(-10, ((float *)_config->Table<float>())[0]);
		Config::OffsetConfig(config, size, sizeof(float) * 40);
		ASSERT_EQ(size, _config->Size());
		ASSERT_EQ(size, _size);
	}

	TEST_F(Operation_2AxisTableTests, WhenGettingValueInTable_ThenCorrectValueIsReturned)
	{
		ASSERT_EQ(-10, _operation->Execute<int8_t>(static_cast<uint8_t>(0), static_cast<int8_t>(0)));
		ASSERT_EQ(20, _operation->Execute<uint8_t>(static_cast<float>(0.99f), static_cast<uint16_t>(0)));
		ASSERT_EQ(0, _operation->Execute<uint16_t>(static_cast<double>(0.33f), static_cast<int16_t>(0)));
		ASSERT_NEAR(-1.25f, _operation->Execute<float>(static_cast<float>(0.28875f), static_cast<uint32_t>(0)), 0.001f);
		ASSERT_EQ(0, _operation->Execute<uint16_t>(static_cast<int32_t>(0), static_cast<float>(1.1f)));
		ASSERT_EQ(30, _operation->Execute<uint16_t>(static_cast<float>(0.99f), static_cast<float>(1.1f)));
		ASSERT_EQ(10, _operation->Execute<int32_t>(static_cast<float>(0.33f), static_cast<float>(1.1f)));
		ASSERT_NEAR(8.75f, _operation->Execute<float>(static_cast<float>(0.28875f), static_cast<float>(1.1f)), 0.001f);
	}

	TEST_F(Operation_2AxisTableTests, WhenGettingValueAboveMaxValue_ThenCorrectValueIsReturned)
	{
		ASSERT_EQ(80, _operation->Execute<uint64_t>(static_cast<float>(100.0f), static_cast<uint64_t>(0)));
	}

	TEST_F(Operation_2AxisTableTests, WhenGettingValueBelowMinValue_ThenCorrectValueIsReturned)
	{
		ASSERT_EQ(-10, _operation->Execute<int64_t>(static_cast<float>(-1.0f), static_cast<uint64_t>(0)));
	}
}
