#include "Operations/OperationFactoryRegister.h"
#include "Operations/Operation_2AxisTable.h"
#include "Operations/Operation_LookupTable.h"
#include "Operations/Operation_Polynomial.h"
#include "Operations/Operation_Math.h"
#include "Operations/Operation_StaticVariable.h"
#include "Operations/Operation_FaultDetection.h"

#ifdef OPERATIONFACTORYREGISTER_H

namespace OperationArchitecture
{
    void OperationFactoryRegister::Register(uint32_t idOffset, OperationFactory *factory)
    {
        factory->Register(idOffset + 1, Operation_2AxisTableCreate);
        factory->Register(idOffset + 2, Operation_LookupTableCreate);
        factory->Register(idOffset + 3, Operation_Polynomial::Create);
        factory->Register(idOffset + 5, Operation_StaticVariable::Create);
        factory->Register(idOffset + 6, Operation_FaultDetection::Create);
        factory->Register(idOffset + 10, &Operation_Add::Instance);
        factory->Register(idOffset + 11, &Operation_Subtract::Instance);
        factory->Register(idOffset + 12, &Operation_Multiply::Instance);
        factory->Register(idOffset + 13, &Operation_Divide::Instance);
        factory->Register(idOffset + 14, &Operation_And::Instance);
        factory->Register(idOffset + 15, &Operation_Or::Instance);
        factory->Register(idOffset + 16, &Operation_GreaterThan::Instance);
        factory->Register(idOffset + 17, &Operation_LessThan::Instance);
        factory->Register(idOffset + 18, &Operation_Equal::Instance);
        factory->Register(idOffset + 19, &Operation_GreaterThanOrEqual::Instance);
        factory->Register(idOffset + 20, &Operation_LessThanOrEqual::Instance);
    }
}

#endif