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
        factory->Register(idOffset + 1, Operation_2AxisTable::Create);
        factory->Register(idOffset + 2, Operation_LookupTable::Create);
        factory->Register(idOffset + 3, Operation_Polynomial::Create);
        factory->Register(idOffset + 4, Operation_Math::Create);
        factory->Register(idOffset + 5, Operation_StaticVariable::Create);
        factory->Register(idOffset + 6, Operation_FaultDetection::Create);
    }
}

#endif