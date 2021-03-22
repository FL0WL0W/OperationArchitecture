#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/OperationFactory.h"
#include "Operations/Operation_Math.h"
using ::testing::AtLeast;
using ::testing::Return;

using namespace OperationArchitecture;

namespace UnitTests
{
	class OperationFactoryTests : public ::testing::Test 
	{
		protected:
		OperationFactory *_factory;
		IOperationBase *_operation;
		unsigned int _size = 0;

		OperationFactoryTests() 
		{
			_factory = new OperationFactory(64);
			_factory->Register(2, Operation_Math::Create);

			void *config = malloc(sizeof(MathOperation) + sizeof(uint32_t));
			void *buildConfig = config;

			//Factory ID 2 + 64 = 66
			*((uint32_t *)buildConfig) = 66;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			*((MathOperation *)buildConfig) = ADD;
			buildConfig = (void *)((MathOperation *)buildConfig + 1);

			_operation = _factory->Create(config, _size);
		}
	};

	TEST_F(OperationFactoryTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(5, _size);
	}

	TEST_F(OperationFactoryTests, CorrectOperationReturned)
	{
		ASSERT_EQ(2, _operation->NumberOfParameters);
		ASSERT_EQ(7, _operation->Execute<int>(5, 2));
		ASSERT_EQ(8, _operation->Execute<int>(6, 2));
	}
}
