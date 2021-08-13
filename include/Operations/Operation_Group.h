#include "Operations/IOperationBase.h"
#include <utility>

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
        void AbstractExecute(Variable **variables) override;
    };
}
#endif