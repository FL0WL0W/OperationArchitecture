#include "Variable.h"
#include <functional>

#ifndef IOPERATION_H
#define IOPERATION_H
namespace OperationArchitecture
{
    struct Operation
    {
        public:
        char NumberOfReturnVariables;
        char NumberOfParameters;
        std::function<void(Variable **)> Execute;
        std::function<void(void)> Destructor;

        ~Operation()
        {
            if(Destructor != 0)
                Destructor();
        }

        Operation(std::function<void(Variable **)> execute, char numberOfReturnVariables, char numberOfParameters) :
            Execute(execute),
            NumberOfReturnVariables(numberOfReturnVariables),
            NumberOfParameters(numberOfParameters)
        {
        }

        template<typename RET, typename... PARAMS>
        Operation(std::function<RET(PARAMS...)> execute)
        {
            NumberOfParameters = sizeof...(PARAMS);
            NumberOfReturnVariables = 1;

            std::index_sequence_for<PARAMS...> paramIndex = std::index_sequence_for<PARAMS...>{};
            Operation(paramIndex, execute);
        }
        
        template<std::size_t... ParamIndex, typename RET, typename... PARAMS>
        Operation(std::index_sequence<ParamIndex...>, std::function<RET(PARAMS...)> execute)
        {
            Execute = [execute] (Variable **variables) { variables[0]->Set(execute(variables[ParamIndex + 1]->To<PARAMS>()...)); };
        }

        template<typename... PARAMS>
        Operation(std::function<void(PARAMS...)> execute)
        {
            NumberOfParameters = sizeof...(PARAMS);
            NumberOfReturnVariables = 0;
            
            std::index_sequence_for<PARAMS...> paramIndex = std::index_sequence_for<PARAMS...>{};
            Operation(paramIndex, execute);
        }
        
        
        template<std::size_t... ParamIndex, typename... PARAMS>
        Operation(std::index_sequence<ParamIndex...>, std::function<void(PARAMS...)> execute)
        {
            Execute = [execute] (Variable **variables) { execute(variables[ParamIndex]->To<PARAMS>()...); };
        }
        
        template<typename... RETS, typename... PARAMS>
        Operation(std::function<std::tuple<RETS...>(PARAMS...)> execute)
        {
            NumberOfParameters = sizeof...(PARAMS);
            NumberOfReturnVariables = sizeof...(RETS);

            std::index_sequence_for<RETS...> retIndex = std::index_sequence_for<RETS...>{};
            std::index_sequence_for<PARAMS...> paramIndex = std::index_sequence_for<PARAMS...>{};
            Operation(retIndex, paramIndex, execute);
        }

        template<std::size_t... RetIndex, std::size_t... ParamIndex, typename... RETS, typename... PARAMS>
        Operation(std::index_sequence<RetIndex...>, std::index_sequence<ParamIndex...>, std::function<std::tuple<RETS...>(PARAMS...)> execute)
        {
            Execute = [this, execute] (Variable **variables) { 
                std::tuple<RETS...> rets = execute(variables[ParamIndex + NumberOfReturnVariables]->template To<PARAMS>()...);
                //this is fucking stupid, why can't i just "variables[RetIndex]->Set(std::get<RetIndex>(rets)...;" ?
                int expand_type[] = { (variables[RetIndex]->Set(std::get<RetIndex>(rets)), 0)... };
            };
        }

        template<typename RET, typename... PARAMS>
        RET ExecuteT(PARAMS... params)
        {
            Variable ret;
            Variable parameters[sizeof...(PARAMS)] = {Variable::Create(params)...};
            Variable *variables[sizeof...(PARAMS) + 1];
            variables[0] = &ret;
            for(size_t i = 0; i < sizeof...(PARAMS); i++)
            {
                variables[i+1] = &parameters[i];
            } 

            Execute(variables);
            return ret.To<RET>();
        }

        template<typename... PARAMS>
        void ExecuteV(PARAMS... params)
        {
            Variable parameters[sizeof...(PARAMS)] = {Variable::Create(params)...};
            Variable *variables[sizeof...(PARAMS)];
            for(int i = 0; i < sizeof...(PARAMS); i++)
            {
                variables[i] = &parameters[i];
            } 

            Execute(variables);
        }
    };
}
#endif