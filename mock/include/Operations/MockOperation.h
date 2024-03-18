#include "Operations/Operation.h"

#ifndef MOCKOPERATION_H
#define MOCKOPERATION_H
namespace OperationArchitecture
{
	template<typename return_t, typename... PARAMS>
	class MockOperation : public Operation<return_t, PARAMS...>
	{
	public:
		return_t ReturnValue;
		std::tuple<PARAMS...> Parameters;
		return_t Execute(PARAMS... parameters) override {
			Parameters = std::tuple<PARAMS...>(parameters...);
			return ReturnValue;
		}
	};
	template<typename... PARAMS>
	class MockOperation<void, PARAMS...> : public Operation<void, PARAMS...>
	{
	public:
		std::tuple<PARAMS...> Parameters;
		void Execute(PARAMS... parameters) override {
			Parameters = std::tuple<PARAMS...>(parameters...);
		}
	};
}
#endif