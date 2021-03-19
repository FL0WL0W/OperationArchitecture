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
            AbstractExecuteImpl(ret, sequence, params);
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
}
#endif