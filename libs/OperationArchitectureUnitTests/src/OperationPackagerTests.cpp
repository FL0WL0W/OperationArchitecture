#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/OperationPackager.h"
#include "Operations/OperationFactory.h"
#include "Operations/Operation_Math.h"
#include "Operations/Operation_StaticVariable.h"
using ::testing::AtLeast;
using ::testing::Return;

using namespace OperationArchitecture;

namespace UnitTests
{
	class OperationPackagerTests : public ::testing::Test 
	{
		protected:
		SystemBus *_systemBus;
		OperationFactory *_factory;
		OperationPackager *_packager;
		Variable _secondParameter;
		IOperationBase *_operation;//subtract with Operation_StaticVariable for the first parameter and variable for the second
		unsigned int _size = 0;
		IOperationBase *_operationImmediateStore;//add with Operation_StaticVariable for the first parameter and variable for the second
		unsigned int _sizeImmediateStore = 0;
		Variable *_storedResult;

		IOperationBase *CreateOperation(bool operationImmediate, uint32_t storeVariableId, unsigned int &size)
		{
			unsigned int configSize = sizeof(PackageOptions) + 
				sizeof(bool) + sizeof(PackageOptions) + sizeof(uint32_t) + //first parameter
				sizeof(bool) + sizeof(uint32_t);//second parameter
			if(operationImmediate)
				configSize += sizeof(MathOperation) + sizeof(uint32_t);
			else
				configSize += sizeof(uint32_t);
			if(storeVariableId > 0)
				configSize += sizeof(uint32_t);
			void *config = malloc(configSize);
			void *buildConfig = config;

			//options
			((PackageOptions *)buildConfig)->OperationImmediate = operationImmediate;
			((PackageOptions *)buildConfig)->StoreVariable = storeVariableId > 0;
			buildConfig = (void *)(((PackageOptions *)buildConfig) + 1);

			//if storing variable, set the id for the result to be stored into
			if(storeVariableId > 0)
			{
				//VariableId
				*((uint32_t *)buildConfig) = storeVariableId;
				buildConfig = (void *)(((uint32_t *)buildConfig) + 1);
			}

			//if operation is to be created, add the config for creating an operation add
			if(operationImmediate)
			{
				//Factory ID 2 + 64 = 66
				*((uint32_t *)buildConfig) = 66;
				buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

				*((MathOperation *)buildConfig) = ADD;
				buildConfig = (void *)((MathOperation *)buildConfig + 1);
			}
			//otherwise, point to the operation in the system bus with id 25, this is subtract
			else
			{
				//OperationID for Subtract
				*((uint32_t *)buildConfig) = 25;
				buildConfig = (void *)(((uint32_t *)buildConfig) + 1);
			}

			//add first paramater as a package
			*((bool *)buildConfig) = true;
			buildConfig = (void *)(((bool *)buildConfig) + 1);

			((PackageOptions *)buildConfig)->OperationImmediate = false;
			((PackageOptions *)buildConfig)->StoreVariable = false;
			buildConfig = (void *)(((PackageOptions *)buildConfig) + 1);

			//operation id for static variable
			*((uint32_t *)buildConfig) = 24;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);


			//add second paramater as a variable
			*((bool *)buildConfig) = false;
			buildConfig = (void *)(((bool *)buildConfig) + 1);

			//id of variable is 5
			*((uint32_t *)buildConfig) = 5;
			buildConfig = (void *)(((uint32_t *)buildConfig) + 1);

			return _packager->Package(config, size);
		}

		OperationPackagerTests() 
		{
			_systemBus = new SystemBus();
			_systemBus->Operations.insert(std::pair<uint32_t, IOperationBase*>(24, new Operation_StaticVariable(Variable::Create(5))));
			_systemBus->Operations.insert(std::pair<uint32_t, IOperationBase*>(25, new Operation_Math(SUBTRACT)));
			_systemBus->Variables.insert(std::pair<uint32_t, Variable*>(5, &_secondParameter));
			_factory = new OperationFactory(64);
			_factory->Register(2, Operation_Math::Create);
			_packager = new OperationPackager(_factory, _systemBus);

			_operationImmediateStore = CreateOperation(true, 4, _sizeImmediateStore);
			_storedResult = _systemBus->Variables.find(4)->second;
			_operation = CreateOperation(false, 0, _size);
		}
	};

	TEST_F(OperationPackagerTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(21, _sizeImmediateStore);
		ASSERT_EQ(16, _size);
	}

	TEST_F(OperationPackagerTests, OperationPackagedandExecutable)
	{
		ASSERT_EQ(0, _operationImmediateStore->NumberOfParameters);
		ASSERT_EQ(true, _operationImmediateStore->ReturnsVariable);
		ASSERT_EQ(0, _operation->NumberOfParameters);
		ASSERT_EQ(true, _operation->ReturnsVariable);

		//5 + 2
		_secondParameter.Set(2);
		ASSERT_EQ(7, _operationImmediateStore->Execute<int>());
		ASSERT_EQ(7, _storedResult->To<int>());

		//5 - 2
		ASSERT_EQ(3, _operation->Execute<int>());
		ASSERT_EQ(7, _storedResult->To<int>());

		//5 + 3
		_secondParameter.Set(3);
		ASSERT_EQ(8, _operationImmediateStore->Execute<int>());
		ASSERT_EQ(8, _storedResult->To<int>());

		//5 - 3
		ASSERT_EQ(2, _operation->Execute<int>());
		ASSERT_EQ(8, _storedResult->To<int>());
	}
}
