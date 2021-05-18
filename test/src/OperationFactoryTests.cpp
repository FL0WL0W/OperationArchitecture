#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/OperationFactory.h"
#include "Operations/Operation_Math.h"
#include "Operations/Operation_Package.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class OperationFactoryTests : public Test
	{
		protected:
		OperationFactory *_factory;
		IOperationBase *_operation;
		IOperationBase *_operationParamater;
		size_t _size = 0;
		size_t _size2 = 0;

		static IOperationBase * CreateWithParameterFunction(const void *config, size_t &sizeOut, int parameter1, int parameter2)
		{
			OperationOrVariable *parameters = new OperationOrVariable[2] { OperationOrVariable(new Variable(parameter1)), OperationOrVariable(new Variable(parameter2)) };
			return new Operation_Package(Operation_Math::Create(config, sizeOut), 0, parameters);
		}

		OperationFactoryTests() 
		{
			_factory = new OperationFactory();
			_factory->Register(2, Operation_Math::Create);
			_factory->Register(3, new CreateWithParameters<int, int>(OperationFactoryTests::CreateWithParameterFunction, 26, 5));

			void *config = malloc(sizeof(MathOperation) + sizeof(uint32_t));
			void *buildConfig = config;

			//Factory ID 2
			*((uint32_t *)buildConfig) = 2;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			*((MathOperation *)buildConfig) = ADD;
			buildConfig = (void *)((MathOperation *)buildConfig + 1);

			_operation = _factory->Create(config, _size);
			free(config);
			


			config = malloc(sizeof(MathOperation) + sizeof(uint32_t));
			buildConfig = config;

			//Factory ID 3
			*((uint32_t *)buildConfig) = 3;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			*((MathOperation *)buildConfig) = SUBTRACT;
			buildConfig = (void *)((MathOperation *)buildConfig + 1);

			_operationParamater  = _factory->Create(config, _size2);
			free(config);
		}
	};

	TEST_F(OperationFactoryTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(5, _size);
		ASSERT_EQ(5, _size2);
	}

	TEST_F(OperationFactoryTests, CorrectOperationReturned)
	{
		ASSERT_EQ(2, _operation->NumberOfParameters);
		ASSERT_EQ(1, _operation->NumberOfReturnVariables);
		ASSERT_EQ(7, _operation->Execute<int>(5, 2));
		ASSERT_EQ(8, _operation->Execute<int>(6, 2));

		ASSERT_EQ(0, _operationParamater->NumberOfParameters);
		ASSERT_EQ(1, _operationParamater->NumberOfReturnVariables);
		ASSERT_EQ(21, _operationParamater->Execute<int>());
	}
}
