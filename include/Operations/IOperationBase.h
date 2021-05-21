#include "Variable.h"

#ifndef IOPERATIONBASE_H
#define IOPERATIONBASE_H
namespace OperationArchitecture
{
    class IOperationBase
    {
        public:
        char NumberOfReturnVariables;
        char NumberOfParameters;
        virtual void AbstractExecute(Variable **variables) = 0;

        template<typename RET, typename... PARAMS>
        RET Execute(PARAMS... params)
        {
            Variable ret;
            Variable parameters[sizeof...(PARAMS)] = {Variable::Create(params)...};
            Variable *variables[sizeof...(PARAMS) + 1];
            variables[0] = &ret;
            for(size_t i = 0; i < sizeof...(PARAMS); i++)
            {
                variables[i+1] = &parameters[i];
            } 

            AbstractExecute(variables);
            return ret.To<RET>();
        }

        template<typename... PARAMS>
        void Execute(PARAMS... params)
        {
            Variable parameters[sizeof...(PARAMS)] = {Variable::Create(params)...};
            Variable *variables[sizeof...(PARAMS)];
            for(int i = 0; i < sizeof...(PARAMS); i++)
            {
                variables[i] = &parameters[i];
            } 

            AbstractExecute(variables);
        }

        void Execute();
    };
}
#endif