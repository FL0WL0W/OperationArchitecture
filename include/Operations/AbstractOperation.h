#include "Variable.h"

#ifndef ABSTRACTOPERATION_H
#define ABSTRACTOPERATION_H
namespace OperationArchitecture
{
    //// Defines an abstract operation
    class AbstractOperation
    {
        public:
        //// The number of return variables for AbstractExecute.
        const uint8_t NumberOfReturnVariables;
        //// The number of parameters for AbstractExecute.
        const uint8_t NumberOfParameters;

		/**
		 * @brief This virtual function is to be implemented by the child abstraction.
         * @param variables This is an array of variables. The first <NumberOfReturnVariables> Variables
         *      are variables that are written to in this function. The remaining <NumberOfParameters> Variables
         *      are input variables to the operation.
		 */
        virtual void AbstractExecute(Variable **variables) = 0;

		/**
		 * @brief Constructor that sets the constant values for NumberOfReturnVariables and NumberOfParameters
         * @param numberOfReturnVariables The number of return variables for AbstractExecute. This value is stored into NumberOfReturnVariables.
         * @param numberOfParameters The number of parameters for AbstractExecute. This value is stored into NumberOfParameters.
		 */
        AbstractOperation(uint8_t numberOfReturnVariables, uint8_t numberOfParameters);

		/**
		 * @brief Default constructor for an operation with no parameters or return variables
		 */
        AbstractOperation();

        virtual ~AbstractOperation();
        
		/**
		 * @brief This template takes the return and parameters and formats them into variables
         * to be fed to AbstractExecute
         * @param params input parameters
         * @return returned variable
		 */
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

		/**
		 * @brief This template takes the parameters and formats them into variables
         * to be fed to AbstractExecute
         * @param params input parameters
		 */
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