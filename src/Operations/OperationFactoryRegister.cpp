#include "Operations/OperationFactoryRegister.h"
#include "Operations/Operation_Package.h"
#include "Operations/Operation_Group.h"
#include "Operations/Operation_2AxisTable.h"
#include "Operations/Operation_LookupTable.h"
#include "Operations/Operation_Polynomial.h"
#include "Operations/Operation_Math.h"
#include "Operations/Operation_StaticVariable.h"
#include "Operations/Operation_FaultDetection.h"
#include "Operations/Operation_UnitConversion.h"

#ifdef OPERATIONFACTORYREGISTER_H

namespace OperationArchitecture
{
    Operation_Add                   *Operation_AddInstance = 0;
    Operation_Subtract              *Operation_SubtractInstance = 0;
    Operation_Multiply              *Operation_MultiplyInstance = 0;
    Operation_Divide                *Operation_DivideInstance = 0;
    Operation_And                   *Operation_AndInstance = 0;
    Operation_Or                    *Operation_OrInstance = 0;
    Operation_GreaterThan           *Operation_GreaterThanInstance = 0;
    Operation_LessThan              *Operation_LessThanInstance = 0;
    Operation_Equal                 *Operation_EqualInstance = 0;
    Operation_GreaterThanOrEqual    *Operation_GreaterThanOrEqualInstance = 0;
    Operation_LessThanOrEqual       *Operation_LessThanOrEqualInstance = 0;
    Operation_Not                   *Operation_NotInstance = 0;

    void OperationFactoryRegister::Register(uint32_t idOffset, OperationFactory *factory, GeneratorMap<Variable> *variableMap)
    {
        factory->Register(idOffset + 0, [factory, variableMap](const void *config, size_t &size){ return Operation_Package::Create(config, size, factory, variableMap); });
        factory->Register(idOffset + 1, [factory](const void *config, size_t &size){ return Operation_Group::Create(config, size, factory); });
        factory->Register(idOffset + 2, Operation_2AxisTableCreate);
        factory->Register(idOffset + 3, Operation_LookupTableCreate);
        factory->Register(idOffset + 4, Operation_Polynomial<float>::Create);
        factory->Register(idOffset + 5, Operation_StaticVariable::Create);
        factory->Register(idOffset + 6, Operation_FaultDetection<float>::Create);
        factory->Register(idOffset + 10, Operation_AddInstance == 0? Operation_AddInstance = new Operation_Add() : Operation_AddInstance);
        factory->Register(idOffset + 11, Operation_SubtractInstance == 0? Operation_SubtractInstance = new Operation_Subtract() : Operation_SubtractInstance);
        factory->Register(idOffset + 12, Operation_MultiplyInstance == 0? Operation_MultiplyInstance = new Operation_Multiply() : Operation_MultiplyInstance);
        factory->Register(idOffset + 13, Operation_DivideInstance == 0? Operation_DivideInstance = new Operation_Divide() : Operation_DivideInstance);
        factory->Register(idOffset + 14, Operation_AndInstance == 0? Operation_AndInstance = new Operation_And() : Operation_AndInstance);
        factory->Register(idOffset + 15, Operation_OrInstance == 0? Operation_OrInstance = new Operation_Or() : Operation_OrInstance);
        factory->Register(idOffset + 16, Operation_GreaterThanInstance == 0? Operation_GreaterThanInstance = new Operation_GreaterThan() : Operation_GreaterThanInstance);
        factory->Register(idOffset + 17, Operation_LessThanInstance == 0? Operation_LessThanInstance = new Operation_LessThan() : Operation_LessThanInstance);
        factory->Register(idOffset + 18, Operation_EqualInstance == 0? Operation_EqualInstance = new Operation_Equal() : Operation_EqualInstance);
        factory->Register(idOffset + 19, Operation_GreaterThanOrEqualInstance == 0? Operation_GreaterThanOrEqualInstance = new Operation_GreaterThanOrEqual() : Operation_GreaterThanOrEqualInstance);
        factory->Register(idOffset + 20, Operation_LessThanOrEqualInstance == 0? Operation_LessThanOrEqualInstance = new Operation_LessThanOrEqual() : Operation_LessThanOrEqualInstance);
        factory->Register(idOffset + 21, Operation_NotInstance == 0? Operation_NotInstance = new Operation_Not() : Operation_NotInstance);
        factory->Register(idOffset + 22, Operation_UnitConversion::Create);
    }
}

#endif