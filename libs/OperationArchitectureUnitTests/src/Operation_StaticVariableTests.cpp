#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_StaticVariable.h"
using ::testing::AtLeast;
using ::testing::Return;

using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_StaticVariableTests : public ::testing::Test 
	{
		protected:
		IOperationBase *_operation;
		unsigned int _size = 0;

		Operation_StaticVariableTests() 
		{			
			void *config = malloc(sizeof(Variable) + 4);
			void *buildConfig = config;

			//Factory ID doesn't matter
			*((uint32_t *)buildConfig) = 1337;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			*((VariableType *)buildConfig) = VariableType::INT16;
			buildConfig = (void *)((VariableType *)buildConfig + 1);

			*((int16_t *)buildConfig) = 250;
			buildConfig = (void *)((int16_t *)buildConfig + 1);

			_operation = Operation_StaticVariable::Create(config, _size);
		}
	};

	TEST_F(Operation_StaticVariableTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(7, _size);
	}

	TEST_F(Operation_StaticVariableTests, WhenExecuting_ReturnsStaticVariable)
	{
		ASSERT_EQ(250, _operation->Execute<int>());
	}
}
