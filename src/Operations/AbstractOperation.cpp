#include "Operations/AbstractOperation.h"
#include "Config.h"

#ifdef ABSTRACTOPERATION_H
namespace OperationArchitecture
{
	void AbstractOperation::Execute()
	{
		AbstractExecute(0);
	}

	AbstractOperation::AbstractOperation() :
		AbstractOperation(0, 0)
	{
		
	}

	AbstractOperation::~AbstractOperation()
	{
		
	}

	AbstractOperation::AbstractOperation(uint8_t numberOfReturnVariables, uint8_t numberOfParameters) :
		NumberOfReturnVariables(numberOfReturnVariables),
		NumberOfParameters(numberOfParameters)
	{
		
	}
}
#endif