#include "Operations/IOperationBase.h"
#include <utility>

#ifndef OPERATION_PACKAGE_H
#define OPERATION_PACKAGE_H
namespace OperationArchitecture
{
    struct OperationOrVariable
    {
        protected:
            bool _operation;
            void *_location;
        public:
            OperationOrVariable()
            {
                _operation = false;
                _location = 0;
            }
            OperationOrVariable(Variable *variable)
            {
                _operation = false;
                _location = variable;
            }
            OperationOrVariable(IOperationBase *operation)
            {
                _operation = true;
                _location = operation;
            }
            void GetValue(Variable &ret)
            {
                if(_operation)
                {
                    reinterpret_cast<IOperationBase *>(_location)->AbstractExecute(ret, 0);
                }
                else
                {
                    ret = *reinterpret_cast<Variable *>(_location);
                }                
            }
    };

    class Operation_Package : public IOperationBase
    {
        protected:
        IOperationBase *_operation;
        OperationOrVariable *_parameters;
        public:
        Operation_Package(IOperationBase *operation, OperationOrVariable *parameters);
        void AbstractExecute(Variable &ret, Variable *params) override;
    };
}
#endif