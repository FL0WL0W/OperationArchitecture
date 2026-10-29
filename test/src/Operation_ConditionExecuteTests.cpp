#include "gtest/gtest.h"
#include "Config.h"
#include "Operations/Operation_ConditionExecute.h"
#include "Operations/OperationFactoryRegister.h"
#include <memory>

using namespace OperationArchitecture;

namespace UnitTests
{
    namespace
    {
        GeneratorMap<Variable> conditionVariableMap;
        OperationFactory conditionFactory;
        const auto conditionFactoryEntries =
            RegisterOperationArchitecture<100, &conditionFactory, &conditionVariableMap>();

        class TrackedOperation : public AbstractOperation
        {
            bool &_destroyed;
        public:
            explicit TrackedOperation(bool &destroyed) : _destroyed(destroyed) { }
            ~TrackedOperation() override { _destroyed = true; }
            void AbstractExecute(Variable **) override { }
        };
    }

    TEST(Operation_ConditionExecuteTests, ReevaluatesConditionAndForwardsChildOutputsAndInputs)
    {
        Operation_ConditionExecute operation(new Operation_Add());
        Variable condition = false;
        Variable output = 99;
        Variable left = 5;
        Variable right = 2;
        Variable *variables[] = { &condition, &output, &left, &right };

        operation.AbstractExecute(variables);
        EXPECT_EQ(99, static_cast<int>(output));

        condition = true;
        operation.AbstractExecute(variables);
        EXPECT_EQ(7, static_cast<int>(output));
        EXPECT_TRUE(static_cast<bool>(condition));
        EXPECT_EQ(5, static_cast<int>(left));
        EXPECT_EQ(2, static_cast<int>(right));

        condition = false;
        left = 20;
        operation.AbstractExecute(variables);
        EXPECT_EQ(7, static_cast<int>(output));

        condition = true;
        operation.AbstractExecute(variables);
        EXPECT_EQ(22, static_cast<int>(output));
    }

    TEST(Operation_ConditionExecuteTests, FalseConditionDoesNotAccessChildVariables)
    {
        Operation_ConditionExecute operation(new Operation_Add());
        Variable condition = false;
        Variable *variables[] = { &condition };
        operation.AbstractExecute(variables);
    }

    TEST(Operation_ConditionExecuteTests, UsesExistingBooleanVariableConversion)
    {
        Operation_ConditionExecute operation(new Operation_StaticVariable(42));
        Variable condition = 1;
        Variable output = 99;
        Variable *variables[] = { &condition, &output };
        operation.AbstractExecute(variables);
        EXPECT_EQ(99, static_cast<int>(output));
    }

    TEST(Operation_ConditionExecuteTests, DeletesOwnedChild)
    {
        bool destroyed = false;
        {
            Operation_ConditionExecute operation(new TrackedOperation(destroyed));
            EXPECT_FALSE(destroyed);
        }
        EXPECT_TRUE(destroyed);
    }

    TEST(Operation_ConditionExecuteTests, MissingConditionOrChildIsSkipped)
    {
        Operation_ConditionExecute operation(new Operation_StaticVariable(42));
        operation.AbstractExecute(nullptr);
        Variable *missingCondition[] = { nullptr };
        operation.AbstractExecute(missingCondition);

        Operation_ConditionExecute missingChild(nullptr);
        Variable condition = true;
        Variable *variables[] = { &condition };
        missingChild.AbstractExecute(variables);
    }

    TEST(Operation_ConditionExecuteTests, FactoryCreatesChildAndAccumulatesConfigurationSize)
    {
        conditionFactory.Register(conditionFactoryEntries.data(), conditionFactoryEntries.size());
        alignas(max_align_t) uint8_t config[64] = {};
        void *buildConfig = config;
        size_t buildSize = 0;
        Config::AssignAndOffset<uint32_t>(buildConfig, buildSize, 123);
        Config::AssignAndOffset<uint32_t>(buildConfig, buildSize, 105);
        Config::AssignAndOffset(buildConfig, buildSize, VariableType::INT16);
        Config::AssignAndOffset<int16_t>(buildConfig, buildSize, 250);

        size_t size = 3;
        std::unique_ptr<AbstractOperation> operation(conditionFactory.Create(config, size));
        ASSERT_NE(nullptr, operation);
        EXPECT_EQ(buildSize + 3, size);

        Variable condition = false;
        Variable output = 99;
        Variable *variables[] = { &condition, &output };
        operation->AbstractExecute(variables);
        EXPECT_EQ(99, static_cast<int>(output));
        condition = true;
        operation->AbstractExecute(variables);
        EXPECT_EQ(250, static_cast<int>(output));
    }

    TEST(Operation_ConditionExecuteTests, FactoryRejectsUnknownChildAndReportsConsumedSize)
    {
        conditionFactory.Register(conditionFactoryEntries.data(), conditionFactoryEntries.size());
        const uint32_t config[] = { 123, 999 };
        size_t size = 0;
        std::unique_ptr<AbstractOperation> operation(conditionFactory.Create(config, size));
        EXPECT_EQ(nullptr, operation);
        EXPECT_EQ(sizeof(config), size);
    }
}
