#include "Operations/IOperationBase.h"
#include <utility>
#include <tuple>

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
            std::index_sequence_for<PARAMS...> paramIndex = std::index_sequence_for<PARAMS...>{};
            AbstractExecuteImpl(paramIndex, variables);
        }

        template<std::size_t... ParamIndex>
        void AbstractExecuteImpl(std::index_sequence<ParamIndex...>, Variable **variables) {
            variables[0]->Set(Execute(variables[ParamIndex + 1]->To<PARAMS>()...));
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
            std::index_sequence_for<PARAMS...> paramIndex = std::index_sequence_for<PARAMS...>{};
            AbstractExecuteImpl(paramIndex, variables);
        }

        template<std::size_t... ParamIndex>
        void AbstractExecuteImpl(std::index_sequence<ParamIndex...>, Variable **variables) {
            Execute(variables[ParamIndex]->To<PARAMS>()...);
        }
    };
    
    template<typename... RETs, typename... PARAMS>
    class IOperation<std::tuple<RETs...>, PARAMS...> : public IOperationBase
    {
        public:
        IOperation() 
        {
            NumberOfParameters = sizeof...(PARAMS);
            NumberOfReturnVariables = sizeof...(RETs);
        }
        virtual std::tuple<RETs...> Execute(PARAMS...) = 0;
        void AbstractExecute(Variable **variables) override
        {
            std::index_sequence_for<RETs...> retIndex = std::index_sequence_for<RETs...>{};
            std::index_sequence_for<PARAMS...> paramIndex = std::index_sequence_for<PARAMS...>{};
            AbstractExecuteImpl(retIndex, paramIndex, variables);
        }

        template<std::size_t... RetIndex, std::size_t... ParamIndex>
        void AbstractExecuteImpl(std::index_sequence<RetIndex...>, std::index_sequence<ParamIndex...>, Variable **variables) {
            std::tuple<RETs...> rets = Execute(variables[ParamIndex + NumberOfReturnVariables]->To<PARAMS>()...);
            //this is fucking stupid, why can't i just "variables[RetIndex]->Set(std::get<RetIndex>(rets)...;" ?
            int expand_type[] = { (variables[RetIndex]->Set(std::get<RetIndex>(rets)), 0)... };
        }
    };
}
#endif