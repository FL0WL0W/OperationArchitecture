#include "Variable.h"

#ifndef IOPERATIONBASE_H
#define IOPERATIONBASE_H
namespace OperationArchitecture
{
    class IOperationBase
    {
        public:
        char NumberOfParameters : 7;
        bool ReturnsVariable;
        virtual void AbstractExecute(Variable &ret, Variable *params) = 0;

        template<typename RET, typename... PARAMS>
        RET Execute(PARAMS... params)
        {
            Variable ret;
            Variable parameters[sizeof...(PARAMS)] = {Variable::Create(params)...};
            AbstractExecute(ret, parameters);
            return ret.To<RET>();
        }
    };
}
#endif