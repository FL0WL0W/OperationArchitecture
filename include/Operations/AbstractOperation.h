#include "Variable.h"

#ifndef ABSTRACTOPERATION_H
#define ABSTRACTOPERATION_H
namespace OperationArchitecture
{
    //// Defines an abstract operation
    class AbstractOperation
    {
        public:
		/**
		 * @brief This virtual function is to be implemented by the child abstraction.
         * @param variables This is an array of variables. The first <NumberOfReturnVariables> Variables
         *      are variables that are written to in this function. The remaining <NumberOfParameters> Variables
         *      are input variables to the operation.
		 */
        virtual void AbstractExecute(Variable **variables) = 0;

        virtual ~AbstractOperation() = default;
        
		/**
		 * @brief This template takes the return and parameters and formats them into variables
         * to be fed to AbstractExecute
         * @param params input parameters
         * @return returned variable
		 */
        template<typename RET, int..., typename... PARAMS>
        RET Execute(PARAMS... params)
        {
            Variable parameters[sizeof...(PARAMS) + 1] = { 0, params... };
            Variable *variables[sizeof...(PARAMS) + 1];
            for(size_t i = 0; i < sizeof...(PARAMS) + 1; i++)
            {
                variables[i] = &parameters[i];
            } 

            AbstractExecute(variables);
            return *variables[0];
        }

		/**
		 * @brief This template takes the parameters and formats them into variables
         * to be fed to AbstractExecute
         * @param params input parameters
		 */
        template<int..., typename... PARAMS>
        void Execute(PARAMS... params)
        {
            Variable parameters[sizeof...(PARAMS)] = { params... };
            Variable *variables[sizeof...(PARAMS)];
            for(size_t i = 0; i < sizeof...(PARAMS); i++)
            {
                variables[i] = &parameters[i];
            } 

            AbstractExecute(variables);
        }

        void Execute()
        {
            AbstractExecute(0);
        }
    };
}
#endif