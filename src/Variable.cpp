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
    template<>
    VariableBase VariableTo<VariableBase>(VariableBase *variable) { return *variable; }
    template<>
    Variable VariableTo<Variable>(VariableBase *variable) { return *variable; }


    template<>
    void VariableSet(VariableBase *variable, uint8_t value)
    {
        variable->Type = VariableType::UINT8;
        *reinterpret_cast<uint8_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, uint16_t value)
    {
        variable->Type = VariableType::UINT16;
        *reinterpret_cast<uint16_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, uint32_t value)
    {
        variable->Type = VariableType::UINT32;
        *reinterpret_cast<uint32_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, uint64_t value)
    {
        variable->Type = VariableType::UINT64;
        *reinterpret_cast<uint64_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, int8_t value)
    {
        variable->Type = VariableType::INT8;
        *reinterpret_cast<int8_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, int16_t value)
    {
        variable->Type = VariableType::INT16;
        *reinterpret_cast<int16_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, int32_t value)
    {
        variable->Type = VariableType::INT32;
        *reinterpret_cast<int32_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, int64_t value)
    {
        variable->Type = VariableType::INT64;
        *reinterpret_cast<int64_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, float value)
    {
        variable->Type = VariableType::FLOAT;
        *reinterpret_cast<float *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, double value)
    {
        variable->Type = VariableType::DOUBLE;
        *reinterpret_cast<double *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, bool value)
    {
        variable->Type = VariableType::BOOLEAN;
        *reinterpret_cast<bool *>(variable->Value) = value;
    }
    template<>
    void VariableSet(VariableBase *variable, VariableBase value)
    {
        variable->Type = value.Type;
        std::memcpy(variable->Value, &value.Value, sizeof(VariableBase::Value));
    }
    template<>
    void VariableSet(VariableBase *variable, Variable value)
    {
        variable->Type = value.Type;
        std::memcpy(variable->Value, &value.Value, sizeof(Variable::Value));
    }
}
#endif