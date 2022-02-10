#include "Variable.h"

#ifndef IOPERATIONBASE_H
#define IOPERATIONBASE_H
namespace OperationArchitecture
{
    class IOperationBase
    {
        public:
        const uint8_t NumberOfReturnVariables;
        const uint8_t NumberOfParameters;
        virtual void AbstractExecute(Variable **variables) = 0;

        IOperationBase();
        IOperationBase(uint8_t numberOfReturnVariables, uint8_t numberOfParameters);

        template<typename RET, int..., typename... PARAMS>
        RET Execute(PARAMS... params)
        {
            Variable parameters[sizeof...(PARAMS) + 1] = { Variable::Create(0), Variable::Create(params)... };
            Variable *variables[sizeof...(PARAMS) + 1];
            for(size_t i = 0; i < sizeof...(PARAMS) + 1; i++)
            {
                variables[i] = &parameters[i];
            } 
            Variable * const ret = variables[0];

            AbstractExecute(variables);
            return ret->To<RET>();
        }

        template<int..., typename... PARAMS>
        void Execute(PARAMS... params)
        {
            Variable parameters[sizeof...(PARAMS)] = { Variable::Create(params)... };
            Variable *variables[sizeof...(PARAMS)];
            for(size_t i = 0; i < sizeof...(PARAMS); i++)
            {
                variables[i] = &parameters[i];
            } 

            AbstractExecute(variables);
        }

        void Execute();
    };
}
#endif