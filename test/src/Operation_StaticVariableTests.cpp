#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/Operation_StaticVariable.h"
#include "Config.h"
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
		size_t _size = 0;
		IOperationBase *_operationOther;
		size_t _sizeOther = 0;
		IOperationBase *_operationBigOther;
		size_t _sizeBigOther = 0;

		Operation_StaticVariableTests() 
		{	
			size_t size = 0;	
			size += sizeof(VariableType);
			size += size % alignof(int16_t);
			size += sizeof(int16_t);
			void *config = malloc(size);
			size = 0;
			void *buildConfig = config;

			*reinterpret_cast<VariableType *>(buildConfig) = VariableType::INT16;
			Config::OffsetConfig(buildConfig, size, sizeof(VariableType));

			Config::AlignConfig(buildConfig, size, alignof(int16_t));
			*reinterpret_cast<int16_t *>(buildConfig) = 250;
			Config::OffsetConfig(buildConfig, size, sizeof(int16_t));

			_operation = Operation_StaticVariable::Create(config, _size);

			size = 0;	
			size = 0;
			size += sizeof(VariableType);
			size += size % alignof(Test);
			size += sizeof(Test);	
			config = malloc(size);
			size = 0;	
			buildConfig = config;

			*reinterpret_cast<VariableType *>(buildConfig) = VariableType::OTHER;
			Config::OffsetConfig(buildConfig, size, sizeof(VariableType));

			Test test;
			test.test1 = 1349;
			test.test2 = 103.2f;

			Config::AlignConfig(buildConfig, size, alignof(Test));
			*reinterpret_cast<Test *>(buildConfig) = test;
			Config::OffsetConfig(buildConfig, size, sizeof(Test));

			_operationOther = Operation_StaticVariable::Create(config, _sizeOther);
						
			size = 0;		
			size += sizeof(VariableType);
			size += size % alignof(uint32_t);
			size += sizeof(uint32_t);
			size += size % alignof(max_align_t);
			size += sizeof(TestBig);
			config = malloc(size);
			size = 0;
			buildConfig = config;

			*reinterpret_cast<VariableType *>(buildConfig) = VariableType::BIGOTHER;
			Config::OffsetConfig(buildConfig, size, sizeof(VariableType));

			Config::AlignConfig(buildConfig, size, alignof(uint32_t));
			*reinterpret_cast<uint32_t *>(buildConfig) = sizeof(TestBig);
			Config::OffsetConfig(buildConfig, size, sizeof(uint32_t));

			TestBig testb;
			testb.test1 = 1339;
			testb.test2 = 102.2f;
			testb.test3 = true;

			Config::AlignConfig(buildConfig, size, alignof(max_align_t));
			*reinterpret_cast<TestBig *>(buildConfig) = testb;
			Config::OffsetConfig(buildConfig, size, sizeof(TestBig));

			_operationBigOther = Operation_StaticVariable::Create(config, _sizeBigOther);
		}
	};

	TEST_F(Operation_StaticVariableTests, ConfigsAreCorrect)
	{
		size_t size = 0;
		size += sizeof(VariableType);
		size += size % alignof(int16_t);
		size += sizeof(int16_t);
		ASSERT_EQ(size, _size);

		size = 0;
		size += sizeof(VariableType);
		size += size % alignof(Test);
		size += sizeof(Test);
		ASSERT_EQ(size, _sizeOther);

		size = 0;		
		size += sizeof(VariableType);
		size += size % alignof(uint32_t);
		size += sizeof(uint32_t);
		size += size % alignof(max_align_t);
		size += sizeof(TestBig);
		ASSERT_EQ(size, _sizeBigOther);
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
