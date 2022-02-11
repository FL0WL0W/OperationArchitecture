#include "Operations/IOperationBase.h"
#include "Config.h"

#ifdef IOPERATIONBASE_H
namespace OperationArchitecture
{
	void IOperationBase::Execute()
	{
		AbstractExecute(0);
	}

	IOperationBase::IOperationBase() :
		IOperationBase(0, 0)
	{
		
	}

	IOperationBase::IOperationBase(uint8_t numberOfReturnVariables, uint8_t numberOfParameters) :
		NumberOfReturnVariables(numberOfReturnVariables),
		NumberOfParameters(numberOfParameters)
	{
		
	}
}
#endif