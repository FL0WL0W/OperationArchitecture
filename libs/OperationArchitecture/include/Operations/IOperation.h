#include "Operations/IOperationBase.h"
#include <utility>

#ifndef IOPERATION_H
#define IOPERATION_H
namespace OperationArchitecture
{
    template<typename RET, typename... PARAMS>
    class IOperation : public IOperationBase
    {
        public:
        IOperation() 
        {
            NumberOfParameters = sizeof...(PARAMS);
            ReturnsVariable = true;
        }
        virtual RET Execute(PARAMS...) = 0;
        void AbstractExecute(Variable &ret, Variable *params) override
        {
            auto sequence = std::index_sequence_for<PARAMS...>{};
            return AbstractExecuteImpl(ret, sequence, params);
        }

        template<std::size_t... S>
        void AbstractExecuteImpl(Variable &ret, std::index_sequence<S...>, Variable *params) {
            ret.Set(Execute(params[S].To<PARAMS>()...));
        }
    };
    
    template<typename... PARAMS>
    class IOperation<void, PARAMS...> : public IOperationBase
    {
        public:
        IOperation() 
        {
            NumberOfParameters = sizeof...(PARAMS);
            ReturnsVariable = false;
        }
        virtual void Execute(PARAMS...) = 0;
        void AbstractExecute(Variable &ret, Variable *params) override
        {
            auto sequence = std::index_sequence_for<PARAMS...>{};
            AbstractExecuteImpl(sequence, params);
        }

        template<std::size_t... S>
        void AbstractExecuteImpl(std::index_sequence<S...>, Variable *params) {
            Execute(params[S].To<PARAMS>()...);
        }
    };

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