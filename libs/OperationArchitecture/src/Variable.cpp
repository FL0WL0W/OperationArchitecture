#include "Variable.h"

#ifdef VARIABLE_H
namespace OperationArchitecture
{
    template<>
    uint8_t VariableTo<uint8_t>(VariableBase *variable) { return VariableBaseTo<uint8_t>(variable); }
    template<>
    uint16_t VariableTo<uint16_t>(VariableBase *variable) { return VariableBaseTo<uint16_t>(variable); }
    template<>
    uint32_t VariableTo<uint32_t>(VariableBase *variable) { return VariableBaseTo<uint32_t>(variable); }
    template<>
    uint64_t VariableTo<uint64_t>(VariableBase *variable) { return VariableBaseTo<uint64_t>(variable); }
    template<>
    int8_t VariableTo<int8_t>(VariableBase *variable) { return VariableBaseTo<int8_t>(variable); }
    template<>
    int16_t VariableTo<int16_t>(VariableBase *variable) { return VariableBaseTo<int16_t>(variable); }
    template<>
    int32_t VariableTo<int32_t>(VariableBase *variable) { return VariableBaseTo<int32_t>(variable); }
    template<>
    int64_t VariableTo<int64_t>(VariableBase *variable) { return VariableBaseTo<int64_t>(variable); }
    template<>
    float VariableTo<float>(VariableBase *variable) { return VariableBaseTo<float>(variable); }
    template<>
    double VariableTo<double>(VariableBase *variable) { return VariableBaseTo<double>(variable); }
    template<>
    bool VariableTo<bool>(VariableBase *Variable)
    {
        if(Variable->Type == VariableType::BOOLEAN)
            return *reinterpret_cast<bool *>(&Variable->Value);
        return false;
    }
}
#endif