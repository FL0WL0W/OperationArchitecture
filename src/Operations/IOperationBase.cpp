#include "Operations/IOperationBase.h"
#include "Config.h"

#ifdef IOPERATIONBASE_H
namespace OperationArchitecture
{
	void IOperationBase::Execute()
	{
		AbstractExecute(0);
	}
}
#endif