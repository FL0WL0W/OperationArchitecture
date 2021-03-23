#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_StaticVariable.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class Operation_StaticVariableTests : public Test
	{
		protected:
		struct Test
		{
			int test1;
			float test2;
		};

		struct TestBig
		{
			int test1;
			float test2;
			bool test3;
		};

		IOperationBase *_operation;
		unsigned int _size = 0;
		IOperationBase *_operationOther;
		unsigned int _sizeOther = 0;
		IOperationBase *_operationBigOther;
		unsigned int _sizeBigOther = 0;

		Operation_StaticVariableTests() 
		{			
			void *config = malloc(sizeof(Variable) + sizeof(uint32_t));
			void *buildConfig = config;

			//Factory ID doesn't matter
			*((uint32_t *)buildConfig) = 1337;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			*((VariableType *)buildConfig) = VariableType::INT16;
			buildConfig = (void *)((VariableType *)buildConfig + 1);

			*((int16_t *)buildConfig) = 250;
			buildConfig = (void *)((int16_t *)buildConfig + 1);

			_operation = Operation_StaticVariable::Create(config, _size);
						
			config = malloc(sizeof(Variable) + sizeof(uint32_t));
			buildConfig = config;

			//Factory ID doesn't matter
			*((uint32_t *)buildConfig) = 1337;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			*((VariableType *)buildConfig) = VariableType::OTHER;
			buildConfig = (void *)((VariableType *)buildConfig + 1);

			Test test;
			test.test1 = 1349;
			test.test2 = 103.2f;

			*((Test *)buildConfig) = test;
			buildConfig = (void *)((Test *)buildConfig + 1);

			_operationOther = Operation_StaticVariable::Create(config, _sizeOther);

						
			config = malloc(sizeof(Variable) + sizeof(uint32_t));
			buildConfig = config;

			//Factory ID doesn't matter
			*((uint32_t *)buildConfig) = 1337;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			*((VariableType *)buildConfig) = VariableType::BIGOTHER;
			buildConfig = (void *)((VariableType *)buildConfig + 1);

			*((uint32_t *)buildConfig) = sizeof(TestBig);
			buildConfig = (void *)((uint32_t *)buildConfig + 1);

			TestBig testb;
			testb.test1 = 1339;
			testb.test2 = 102.2f;
			testb.test3 = true;

			*((TestBig *)buildConfig) = testb;
			buildConfig = (void *)((TestBig *)buildConfig + 1);

			_operationBigOther = Operation_StaticVariable::Create(config, _sizeBigOther);
		}
	};

	TEST_F(Operation_StaticVariableTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(7, _size);
		ASSERT_EQ(9 + sizeof(TestBig), _sizeBigOther);
		ASSERT_EQ(13, _sizeOther);
	}

	TEST_F(Operation_StaticVariableTests, WhenExecuting_ReturnsStaticVariable)
	{
		ASSERT_EQ(250, _operation->Execute<int>());

		ASSERT_EQ(1349, _operationOther->Execute<Test>().test1);
		ASSERT_FLOAT_EQ(103.2f, _operationOther->Execute<Test>().test2);

		ASSERT_EQ(1339, _operationBigOther->Execute<TestBig>().test1);
		ASSERT_FLOAT_EQ(102.2f, _operationBigOther->Execute<TestBig>().test2);
		ASSERT_EQ(true, _operationBigOther->Execute<TestBig>().test3);
	}
}
