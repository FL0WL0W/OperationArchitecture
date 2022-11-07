#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_UnitConversion.h"
#include "Config.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_UnitConversionTests : public Test
	{
		protected:
		IOperationBase *_operation;
		size_t _size = 0;
		size_t _expectedSize = 0;
		size_t _buildSize = 0;

		Operation_UnitConversionTests() 
		{	
			_expectedSize = sizeof(float);
			Config::AlignAndAddSize<float>(_expectedSize);
			void *config = malloc(_expectedSize);
			void *buildConfig = config;

			//multiplier
			Config::AssignAndOffset<float>(buildConfig, _buildSize, 5);
			//adder
			Config::AssignAndOffset<float>(buildConfig, _buildSize, 5);
			_operation = Operation_UnitConversion::Create(config, _size);
		}
	};

	TEST_F(Operation_UnitConversionTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSize);
		ASSERT_EQ(_expectedSize, _size);
	}

	TEST_F(Operation_UnitConversionTests, WhenExecuting_ReturnsConvertedUnit)
	{
		ASSERT_EQ(30, _operation->Execute<float>(5));
		ASSERT_EQ(55, _operation->Execute<float>(10));
	}
}
