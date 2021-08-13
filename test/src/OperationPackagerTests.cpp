#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Operations/OperationPackager.h"
#include "Operations/OperationFactory.h"
#include "Operations/Operation_Math.h"
#include "Operations/Operation_StaticVariable.h"
#include "Config.h"
using namespace testing;
using namespace OperationArchitecture;

namespace UnitTests
{
	class OperationPackagerTests : public Test
	{
		protected:
		SystemBus *_systemBus;
		OperationFactory *_factory;
		OperationPackager *_packager;
		Variable _secondParameter;
		IOperationBase *_operation;//subtract with Operation_StaticVariable for the first parameter and variable for the second
		size_t _size = 0;
		size_t _expectedSize = 0;
		IOperationBase *_operationImmediateStore;//add with Operation_StaticVariable for the first parameter and variable for the second
		size_t _sizeImmediateStore = 0;
		size_t _expectedSizeImmediateStore = 0;
		Variable *_storedResult;
		IOperationBase *_operationGroup;//operation group add then subtract;
		size_t _sizeGroup = 0;
		size_t _expectedSizeGroup = 0;

		void CreateOperationConfig(void *&buildConfig, size_t &size, bool operationImmediate, uint32_t storeVariableId)
		{
			//options
			Config::AlignConfig(buildConfig, size, alignof(PackageOptions));
			reinterpret_cast<PackageOptions *>(buildConfig)->OperationImmediate = operationImmediate;
			reinterpret_cast<PackageOptions *>(buildConfig)->StoreVariables = storeVariableId > 0;
			reinterpret_cast<PackageOptions *>(buildConfig)->ReturnVariables = 1;
			reinterpret_cast<PackageOptions *>(buildConfig)->Group = false;
			Config::OffsetConfig(buildConfig, size, sizeof(PackageOptions));

			//if operation is to be created, add the config for creating an operation add
			if(operationImmediate)
			{
				//Factory ID 2
				Config::AssignAndOffset<uint32_t>(buildConfig, size, 2);
			}
			//otherwise, point to the operation in the system bus with id 25, this is subtract
			else
			{
				//OperationID for Subtract
				Config::AssignAndOffset<uint32_t>(buildConfig, size, 25);
			}

			//if storing variables, set the id for the result to be stored into
			if(storeVariableId > 0)
			{
				//VariableId
				Config::AssignAndOffset(buildConfig, size, storeVariableId);
			}

			//add first paramater as a package
			Config::AssignAndOffset<uint8_t>(buildConfig, size, 1);
			Config::AssignAndOffset<uint8_t>(buildConfig, size, 0);

			//add second paramater as a variable
			Config::AssignAndOffset<uint8_t>(buildConfig, size, 0);

			//id of variable is 5
			Config::AssignAndOffset<uint32_t>(buildConfig, size, 5);

			//add configuration for pacakge parameter
			Config::AlignConfig(buildConfig, size, alignof(PackageOptions));
			reinterpret_cast<PackageOptions *>(buildConfig)->OperationImmediate = false;
			reinterpret_cast<PackageOptions *>(buildConfig)->StoreVariables = false;
			reinterpret_cast<PackageOptions *>(buildConfig)->ReturnVariables = 1;
			reinterpret_cast<PackageOptions *>(buildConfig)->Group = false;
			Config::OffsetConfig(buildConfig, size, sizeof(PackageOptions));

			//operation id for static variable
			Config::AssignAndOffset<uint32_t>(buildConfig, size, 24);
		}

		OperationPackagerTests() 
		{
			_systemBus = new SystemBus();
			_systemBus->Operations.insert(std::pair<uint32_t, IOperationBase*>(24, new Operation_StaticVariable(Variable::Create(5))));
			_systemBus->Operations.insert(std::pair<uint32_t, IOperationBase*>(25, &Operation_Subtract::Instance));
			_systemBus->Variables.insert(std::pair<uint32_t, Variable*>(5, &_secondParameter));
			_factory = new OperationFactory();
			_factory->Register(2, &Operation_Add::Instance);
			_packager = new OperationPackager(_factory, _systemBus);

			void *configOperationImmediate = malloc(100);
			void *buildConfig = configOperationImmediate;
			CreateOperationConfig(buildConfig, _expectedSizeImmediateStore, true, 4);
			_operationImmediateStore = _packager->Package(configOperationImmediate, _sizeImmediateStore);

			_storedResult = _systemBus->Variables.find(4)->second;

			void *configOperation = malloc(100);
			buildConfig = configOperation;
			CreateOperationConfig(buildConfig, _expectedSize, false, 0);
			_operation = _packager->Package(configOperation, _size);

			void *configGroup = malloc(100);
			buildConfig = configGroup;

			//options
			reinterpret_cast<PackageOptions *>(buildConfig)->OperationImmediate = true;
			reinterpret_cast<PackageOptions *>(buildConfig)->StoreVariables = false;
			reinterpret_cast<PackageOptions *>(buildConfig)->ReturnVariables = true;
			reinterpret_cast<PackageOptions *>(buildConfig)->Group = true;
			Config::OffsetConfig(buildConfig, _expectedSizeGroup, sizeof(PackageOptions));

			//2 operations
			Config::AssignAndOffset<uint16_t>(buildConfig, _expectedSizeGroup, 2);

            CreateOperationConfig(buildConfig, _expectedSizeGroup, true, 4);
            CreateOperationConfig(buildConfig, _expectedSizeGroup, false, 0);

			_operationGroup = _packager->Package(configGroup, _sizeGroup);
		}
	};

	TEST_F(OperationPackagerTests, ConfigsAreCorrect)
	{
		ASSERT_EQ(_expectedSizeImmediateStore, _sizeImmediateStore);
		ASSERT_EQ(_expectedSize, _size);
		ASSERT_EQ(_expectedSizeGroup, _sizeGroup);
	}

	TEST_F(OperationPackagerTests, OperationPackagedandExecutable)
	{
		ASSERT_EQ(0, _operationImmediateStore->NumberOfParameters);
		ASSERT_EQ(0, _operation->NumberOfParameters);
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

		_secondParameter.Set(4);

		Variable **variables = new Variable*[2];
		for(int i = 0; i < 2; i++)
			variables[i] = new Variable();
		_operationGroup->AbstractExecute(variables);

		//5 + 4
		ASSERT_EQ(9, variables[0]->To<int>());
		ASSERT_EQ(9, _storedResult->To<int>());

		//5 - 4
		ASSERT_EQ(1, variables[1]->To<int>());
	}
}
