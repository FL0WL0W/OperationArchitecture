#include "GeneratorMap.h"
#include "Operations/OperationFactory.h"
#include "Operations/Operation_Package.h"
#include "Operations/Operation_Group.h"
#include "Operations/Operation_ConditionExecute.h"
#include "Operations/Operation_2AxisTable.h"
#include "Operations/Operation_LookupTable.h"
#include "Operations/Operation_Polynomial.h"
#include "Operations/Operation_Math.h"
#include "Operations/Operation_StaticVariable.h"
#include "Operations/Operation_FaultDetection.h"
#include "Operations/Operation_UnitConversion.h"

#ifndef OPERATIONFACTORYREGISTER_H
#define OPERATIONFACTORYREGISTER_H
namespace OperationArchitecture
{
    extern Operation_Add                   Operation_AddInstance;
    extern Operation_Subtract              Operation_SubtractInstance;
    extern Operation_Multiply              Operation_MultiplyInstance;
    extern Operation_Divide                Operation_DivideInstance;
    extern Operation_And                   Operation_AndInstance;
    extern Operation_Or                    Operation_OrInstance;
    extern Operation_GreaterThan           Operation_GreaterThanInstance;
    extern Operation_LessThan              Operation_LessThanInstance;
    extern Operation_Equal                 Operation_EqualInstance;
    extern Operation_GreaterThanOrEqual    Operation_GreaterThanOrEqualInstance;
    extern Operation_LessThanOrEqual       Operation_LessThanOrEqualInstance;
    extern Operation_Not                   Operation_NotInstance;
    extern Operation_NotEqual              Operation_NotEqualInstance;

	template<uint32_t idOffset, OperationFactory *factory, GeneratorMap<Variable> *variableMap>
	constexpr auto RegisterOperationArchitecture = []() {
		return std::array<OperationFactoryEntry, 22>{{
			{ idOffset + 0, [](const void *config, size_t &size){ return Operation_Package::Create(config, size, factory, variableMap); } },
			{ idOffset + 1, [](const void *config, size_t &size){ return Operation_Group::Create(config, size, factory); } },
			{ idOffset + 2, Operation_2AxisTableCreate },
			{ idOffset + 3, Operation_LookupTableCreate },
			{ idOffset + 4, Operation_Polynomial<float>::Create },
			{ idOffset + 5, Operation_StaticVariable::Create },
			{ idOffset + 6, Operation_FaultDetection<float>::Create },
			{ idOffset + 9, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_NotEqualInstance); } },
			{ idOffset + 10, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_AddInstance); } },
			{ idOffset + 11, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_SubtractInstance); } },
			{ idOffset + 12, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_MultiplyInstance); } },
			{ idOffset + 13, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_DivideInstance); } },
			{ idOffset + 14, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_AndInstance); } },
			{ idOffset + 15, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_OrInstance); } },
			{ idOffset + 16, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_GreaterThanInstance); } },
			{ idOffset + 17, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_LessThanInstance); } },
			{ idOffset + 18, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_EqualInstance); } },
			{ idOffset + 19, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_GreaterThanOrEqualInstance); } },
			{ idOffset + 20, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_LessThanOrEqualInstance); } },
			{ idOffset + 21, [](const void *config, size_t &size){ return static_cast<AbstractOperation *>(&Operation_NotInstance); } },
			{ idOffset + 22, Operation_UnitConversion::Create },
    		{ idOffset + 23, [](const void *config, size_t &size){ return Operation_ConditionExecute::Create(config, size, factory); } }
		}};
	};
}
#endif
