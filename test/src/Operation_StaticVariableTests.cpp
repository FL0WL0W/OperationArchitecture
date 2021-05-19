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
		size_t _expectedSize = 0;
		size_t _buildSize = 0;
		IOperationBase *_operationOther;
		size_t _sizeOther = 0;
		size_t _expectedSizeOther = 0;
		size_t _buildSizeOther = 0;
		IOperationBase *_operationBigOther;
		size_t _sizeBigOther = 0;
		size_t _expectedSizeBigOther = 0;
		size_t _buildSizeBigOther = 0;

		Operation_StaticVariableTests() 
		{	
			_expectedSize = sizeof(VariableType);
			Config::AlignAndAddSize<int16_t>(_expectedSize);
			void *config = malloc(_expectedSize);
			void *buildConfig = config;

			Config::AssignAndOffset(buildConfig, _buildSize, VariableType::INT16);
			Config::AssignAndOffset<int16_t>(buildConfig, _buildSize, 250);
			_operation = Operation_StaticVariable::Create(config, _size);


			_expectedSizeOther = sizeof(VariableType);
			Config::AlignAndAddSize<uint64_t>(_expectedSizeOther);//size and align of other is a uint64_t
			config = malloc(_expectedSizeOther);
			buildConfig = config;

			Config::AssignAndOffset(buildConfig, _buildSizeOther, VariableType::OTHER);
			Test test;
			test.test1 = 1349;
			test.test2 = 103.2f;
			Config::AssignAndOffset(buildConfig, _buildSizeOther, *reinterpret_cast<uint64_t *>(&test));
			_operationOther = Operation_StaticVariable::Create(config, _sizeOther);
						
			_expectedSizeBigOther = sizeof(VariableType);
			Config::AlignAndAddSize<uint32_t>(_expectedSizeBigOther);
			if(_expectedSizeBigOther % alignof(max_align_t) != 0)
				_expectedSizeBigOther += alignof(max_align_t) - _expectedSizeBigOther % alignof(max_align_t);
			_expectedSizeBigOther += sizeof(TestBig);
			config = malloc(_expectedSizeBigOther);
			buildConfig = config;

			Config::AssignAndOffset(buildConfig, _buildSizeBigOther, VariableType::BIGOTHER);
			Config::AssignAndOffset<uint32_t>(buildConfig, _buildSizeBigOther, sizeof(TestBig));
			TestBig testb;
			testb.test1 = 1339;
			testb.test2 = 102.2f;
			testb.test3 = true;
			//unknown type means we have to max align
			Config::AlignConfig(buildConfig, _buildSizeBigOther, alignof(max_align_t));
			Config::AssignAndOffset(buildConfig, _buildSizeBigOther, testb);
			_operationBigOther = Operation_StaticVariable::Create(config, _sizeBigOther);
		}
	};

	TEST_F(Operation_StaticVariableTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSize);
		ASSERT_EQ(_expectedSize, _size);

		ASSERT_EQ(_expectedSizeOther, _buildSizeOther);
		ASSERT_EQ(_expectedSizeOther, _sizeOther);

		ASSERT_EQ(_expectedSizeBigOther, _buildSizeBigOther);
		ASSERT_EQ(_expectedSizeBigOther, _sizeBigOther);
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
