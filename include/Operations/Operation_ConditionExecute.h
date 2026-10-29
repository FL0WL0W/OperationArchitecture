#include "Operations/AbstractOperation.h"
#include "Operations/OperationFactory.h"

#ifndef OPERATION_CONDITIONEXECUTE_H
#define OPERATION_CONDITIONEXECUTE_H
namespace OperationArchitecture
{
    class Operation_ConditionExecute : public AbstractOperation
    {
    protected:
        AbstractOperation *_operation;

    public:
        // Takes ownership of operation, which must be independently deletable.
        explicit Operation_ConditionExecute(AbstractOperation *operation);
        ~Operation_ConditionExecute() override;

        Operation_ConditionExecute(const Operation_ConditionExecute &) = delete;
        Operation_ConditionExecute &operator=(const Operation_ConditionExecute &) = delete;

        // variables[0] is a Boolean condition. The child receives variables + 1,
        // including its output variables, only when the condition is true.
        void AbstractExecute(Variable **variables) override;

        // Config contains the child operation's factory ID and configuration.
        static AbstractOperation *Create(const void *config, size_t &sizeOut, OperationFactory *factory);
    };
}
#endif
