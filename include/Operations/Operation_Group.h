#include "Operations/IOperationBase.h"
#include "Operations/OperationFactory.h"

#ifndef OPERATION_GROUP_H
#define OPERATION_GROUP_H
namespace OperationArchitecture
{
    class Operation_Group : public IOperationBase
    {
    protected:
        IOperationBase * const * const _operations;
        const uint16_t _numberOfOperations;
    public:
        Operation_Group(IOperationBase * const * const operations, const uint16_t &numberOfOperations);
        ~Operation_Group();

        void AbstractExecute(Variable **variables) override;

		static IOperationBase *Create(const void *config, size_t &sizeOut, OperationFactory *factory);
    };
}
#endif