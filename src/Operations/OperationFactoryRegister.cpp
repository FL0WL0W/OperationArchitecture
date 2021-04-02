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
    void OperationFactoryRegister::Register(OperationFactory *factory)
    {
        factory->Register(1, Operation_2AxisTable::Create);
        factory->Register(2, Operation_LookupTable::Create);
        factory->Register(3, Operation_Polynomial::Create);
        factory->Register(4, Operation_Math::Create);
        factory->Register(5, Operation_StaticVariable::Create);
        factory->Register(6, Operation_FaultDetection::Create);
    }
}

#endif