#include "Operations/IOperationBase.h"
#include <utility>
#include <tuple>

#ifndef IOPERATION_H
#define IOPERATION_H
namespace OperationArchitecture
{
#if __cplusplus > 201103L
	template<std::size_t... Ints>
	using index_sequence = std::index_sequence<Ints...>;

	template<typename... T>
	using index_sequence_for = std::index_sequence_for<T...>;
#else
	template<typename T, T... Ints>
	struct integer_sequence
	{
		typedef T value_type;
		static constexpr std::size_t size() { return sizeof...(Ints); }
	};
	
	template<std::size_t... Ints>
	using index_sequence = integer_sequence<std::size_t, Ints...>;
	
	template<typename T, std::size_t N, T... Is>
	struct make_integer_sequence : make_integer_sequence<T, N-1, N-1, Is...> {};
	
	template<typename T, T... Is>
	struct make_integer_sequence<T, 0, Is...> : integer_sequence<T, Is...> {};
	
	template<std::size_t N>
	using make_index_sequence = make_integer_sequence<std::size_t, N>;
	
	template<typename... T>
	using index_sequence_for = make_index_sequence<sizeof...(T)>;
#endif

    template<typename RET, typename... PARAMS>
    class IOperation : public IOperationBase
    {
        public:
        IOperation() : IOperationBase(1, sizeof...(PARAMS)) {}
        virtual RET Execute(PARAMS...) = 0;
        void AbstractExecute(Variable **variables) override
        {
            index_sequence_for<PARAMS...> paramIndex = index_sequence_for<PARAMS...>{};
            AbstractExecuteImpl(paramIndex, variables);
        }

        template<std::size_t... ParamIndex>
        void AbstractExecuteImpl(index_sequence<ParamIndex...>, Variable **variables) {
            variables[0]->Set(Execute(variables[ParamIndex + 1]->To<PARAMS>()...));
        }
    };
    
    template<typename... PARAMS>
    class IOperation<void, PARAMS...> : public IOperationBase
    {
        public:
        IOperation() : IOperationBase(0, sizeof...(PARAMS)) {}
        virtual void Execute(PARAMS...) = 0;
        void AbstractExecute(Variable **variables) override
        {
            index_sequence_for<PARAMS...> paramIndex = index_sequence_for<PARAMS...>{};
            AbstractExecuteImpl(paramIndex, variables);
        }

        template<std::size_t... ParamIndex>
        void AbstractExecuteImpl(index_sequence<ParamIndex...>, Variable **variables) {
            Execute(variables[ParamIndex]->To<PARAMS>()...);
        }
    };
    
    template<typename... RETs, typename... PARAMS>
    class IOperation<std::tuple<RETs...>, PARAMS...> : public IOperationBase
    {
        public:
        IOperation() : IOperationBase(sizeof...(RETs), sizeof...(PARAMS)) {}
        virtual std::tuple<RETs...> Execute(PARAMS...) = 0;
        void AbstractExecute(Variable **variables) override
        {
            index_sequence_for<RETs...> retIndex = index_sequence_for<RETs...>{};
            index_sequence_for<PARAMS...> paramIndex = index_sequence_for<PARAMS...>{};
            AbstractExecuteImpl(retIndex, paramIndex, variables);
        }

        template<std::size_t... RetIndex, std::size_t... ParamIndex>
        void AbstractExecuteImpl(index_sequence<RetIndex...>, index_sequence<ParamIndex...>, Variable **variables) {
            std::tuple<RETs...> rets = Execute(variables[ParamIndex + NumberOfReturnVariables]->template To<PARAMS>()...);
            //this is fucking stupid, why can't i just "variables[RetIndex]->Set(std::get<RetIndex>(rets)...;" ?
            int expand_type[] = { (variables[RetIndex]->Set(std::get<RetIndex>(rets)), 0)... };
        }
    };
}
#endif