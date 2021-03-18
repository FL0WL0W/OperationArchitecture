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
    };
}
#endif