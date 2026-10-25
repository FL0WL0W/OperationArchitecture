#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/OperationFactory.h"
#include "Operations/OperationFactoryRegister.h"
#include "Operations/Operation_Math.h"
#include "Operations/Operation_Package.h"
#include "Config.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	static GeneratorMap<Variable> _variableMap;
	static OperationFactory _factory;
	static auto _factoryEntries = CombineEntries(
		RegisterOperationArchitecture<0, &_factory, &_variableMap>()
	);

	class OperationFactoryTests : public Test
	{
		protected:
		AbstractOperation *_operation2;
		AbstractOperation *_operation3;
		size_t _size = 0;
		size_t _size2 = 0;
		size_t _expectedSize = 0;
		size_t _expectedSize2 = 0;
		size_t _buildSize = 0;
		size_t _buildSize2 = 0;

		OperationFactoryTests() 
		{
			_factory.Register(_factoryEntries.data(), _factoryEntries.size());

			_expectedSize = sizeof(uint32_t);
			void *config = malloc(_expectedSize);
			void *buildConfig = config;

			//Factory ID 10
			Config::AssignAndOffset<uint32_t>(buildConfig, _buildSize, 10);

			_operation2 = _factory.Create(config, _size);
			free(config);
			
			_expectedSize2 = sizeof(uint32_t);
			config = malloc(_expectedSize2);
			buildConfig = config;

			//Factory ID 11
			Config::AssignAndOffset<uint32_t>(buildConfig, _buildSize2, 11);

			_operation3  = _factory.Create(config, _size2);
			free(config);
		}
	};

	TEST_F(OperationFactoryTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSize, _buildSize);
		ASSERT_EQ(_expectedSize, _size);
		ASSERT_EQ(_expectedSize2, _buildSize2);
		ASSERT_EQ(_expectedSize2, _size2);
	}

	TEST_F(OperationFactoryTests, CorrectOperationReturned)
	{
		ASSERT_EQ(7, _operation2->Execute<int>(5, 2));
		ASSERT_EQ(8, _operation2->Execute<int>(6, 2));

		ASSERT_EQ(3, _operation3->Execute<int>(5, 2));
		ASSERT_EQ(3, _operation3->Execute<int>(5, 2));
	}
}
