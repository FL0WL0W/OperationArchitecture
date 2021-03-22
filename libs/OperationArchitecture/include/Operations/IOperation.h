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
            NumberOfParameters = sizeof...(PARAMS) + 1;
            NumberOfReturnVariables = 0;
        }
        virtual RET Execute(PARAMS...) = 0;
        void AbstractExecute(Variable **variables) override
        {
            auto sequence = std::index_sequence_for<PARAMS...>{};
            AbstractExecuteImpl(sequence, variables);
        }

        template<std::size_t... S>
        void AbstractExecuteImpl(std::index_sequence<S...>, Variable **variables) {
            variables[0]->Set(Execute(variables[S + 1]->To<PARAMS>()...));
        }
    };
    
    template<typename... PARAMS>
    class IOperation<void, PARAMS...> : public IOperationBase
    {
        public:
        IOperation() 
        {
            NumberOfParameters = sizeof...(PARAMS);
            NumberOfReturnVariables = 0;
        }
        virtual void Execute(PARAMS...) = 0;
        void AbstractExecute(Variable **variables) override
        {
            auto sequence = std::index_sequence_for<PARAMS...>{};
            AbstractExecuteImpl(sequence, variables);
        }

        template<std::size_t... S>
        void AbstractExecuteImpl(std::index_sequence<S...>, Variable **variables) {
            Execute(variables[S]->To<PARAMS>()...);
        }
    };
}
#endif