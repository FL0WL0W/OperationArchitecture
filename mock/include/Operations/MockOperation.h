#include "Operations/Operation.h"

#ifndef MOCKOPERATION_H
#define MOCKOPERATION_H
namespace OperationArchitecture
{
	template<typename return_t>
	class MockOperation : public Operation<return_t>
	{
	public:
		return_t ReturnValue;
		return_t Execute() override {
			return ReturnValue;
		}
	};
}
#endif