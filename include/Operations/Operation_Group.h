#include "Operations/AbstractOperation.h"
#include "Operations/OperationFactory.h"

#ifndef OPERATION_GROUP_H
#define OPERATION_GROUP_H
namespace OperationArchitecture
{
    class Operation_Group : public AbstractOperation
    {
    protected:
        AbstractOperation * const * const _operations;
        const uint16_t _numberOfOperations;
        Variable** _operationVariables;
    public:
        Operation_Group(AbstractOperation * const * const operations, const uint16_t &numberOfOperations);
        ~Operation_Group();

        void AbstractExecute(Variable **variables) override;

		static AbstractOperation *Create(const void *config, size_t &sizeOut, OperationFactory *factory);
    };
}
#endif