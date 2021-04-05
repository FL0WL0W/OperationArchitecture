#include "Operations/IOperationBase.h"
#include <utility>

#ifndef OPERATION_GROUP_H
#define OPERATION_GROUP_H
namespace OperationArchitecture
{
    class Operation_Group : public IOperationBase
    {
        protected:
        IOperationBase **_operations;
        uint16_t _numberOfOperations;
        public:
        Operation_Group(IOperationBase **operations, uint16_t numberOfOperations);
        void AbstractExecute(Variable **variables) override;
    };
}
#endif