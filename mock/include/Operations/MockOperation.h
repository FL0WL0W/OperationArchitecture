#include "Operations/IOperation.h"

#ifndef MOCKOPERATION_H
#define MOCKOPERATION_H
namespace OperationArchitecture
{
	template<typename return_t>
	class MockOperation : public IOperation<return_t>
	{
	public:
		return_t ReturnValue;
		return_t Execute() override {
			return ReturnValue;
		}
	};
}
#endif