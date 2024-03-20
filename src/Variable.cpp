#include "Variable.h"

#ifdef VARIABLE_H
namespace OperationArchitecture
{
    template<typename K>
    const K VariableScalarTo(const Variable *variable)
    {
        switch(variable->Type)
        {
            case VariableType::UINT8: return static_cast<const K>(*reinterpret_cast<const uint8_t *>(variable->Value));
            case VariableType::UINT16: return static_cast<const K>(*reinterpret_cast<const uint16_t *>(variable->Value));
            case VariableType::UINT32: return static_cast<const K>(*reinterpret_cast<const uint32_t *>(variable->Value));
            case VariableType::UINT64: return static_cast<const K>(*reinterpret_cast<const uint64_t *>(variable->Value));
            case VariableType::INT8: if(static_cast<const K>(-1) > 0 && *reinterpret_cast<const int8_t *>(variable->Value) < 0) return 0; return static_cast<const K>(*reinterpret_cast<const int8_t *>(variable->Value));
            case VariableType::INT16: if(static_cast<const K>(-1) > 0 && *reinterpret_cast<const int16_t *>(variable->Value) < 0) return 0; return static_cast<const K>(*reinterpret_cast<const int16_t *>(variable->Value));
            case VariableType::INT32: if(static_cast<const K>(-1) > 0 && *reinterpret_cast<const int32_t *>(variable->Value) < 0) return 0; return static_cast<const K>(*reinterpret_cast<const int32_t *>(variable->Value));
            case VariableType::INT64: if(static_cast<const K>(-1) > 0 && *reinterpret_cast<const int64_t *>(variable->Value) < 0) return 0; return static_cast<const K>(*reinterpret_cast<const int64_t *>(variable->Value));
            case VariableType::FLOAT: if(static_cast<const K>(-1) > 0 && *reinterpret_cast<const float *>(variable->Value) < 0) return 0; return static_cast<const K>(*reinterpret_cast<const float *>(variable->Value));
            case VariableType::DOUBLE: if(static_cast<const K>(-1) > 0 && *reinterpret_cast<const double *>(variable->Value) < 0) return 0; return static_cast<const K>(*reinterpret_cast<const double *>(variable->Value));
            case VariableType::BOOLEAN: return static_cast<const K>(*reinterpret_cast<const bool *>(variable->Value));
            default:
                return 0;
        }
    }

    template<>
    uint8_t VariableTo<uint8_t>(const Variable *variable)  { return VariableScalarTo<uint8_t>(variable); }
    template<>
    uint16_t VariableTo<uint16_t>(const Variable *variable) { return VariableScalarTo<uint16_t>(variable); }
    template<>
    uint32_t VariableTo<uint32_t>(const Variable *variable) { return VariableScalarTo<uint32_t>(variable); }
    template<>
    uint64_t VariableTo<uint64_t>(const Variable *variable) { return VariableScalarTo<uint64_t>(variable); }
    template<>
    int8_t VariableTo<int8_t>(const Variable *variable) { return VariableScalarTo<int8_t>(variable); }
    template<>
    int16_t VariableTo<int16_t>(const Variable *variable) { return VariableScalarTo<int16_t>(variable); }
    template<>
    int32_t VariableTo<int32_t>(const Variable *variable) { return VariableScalarTo<int32_t>(variable); }
    template<>
    int64_t VariableTo<int64_t>(const Variable *variable) { return VariableScalarTo<int64_t>(variable); }
    template<>
    float VariableTo<float>(const Variable *variable) { return VariableScalarTo<float>(variable); }
    template<>
    double VariableTo<double>(const Variable *variable) { return VariableScalarTo<double>(variable); }
    template<>
    bool VariableTo<bool>(const Variable *Variable)
    {
        if(Variable->Type == VariableType::BOOLEAN)
            return *reinterpret_cast<const bool *>(&Variable->Value);
        return false;
    }
    template<>
    Variable VariableTo<Variable>(const Variable *variable) { return *variable; }


    template<>
    void VariableSet(Variable *variable, uint8_t value)
    {
        variable->Type = VariableType::UINT8;
        *reinterpret_cast<uint8_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, uint16_t value)
    {
        variable->Type = VariableType::UINT16;
        *reinterpret_cast<uint16_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, uint32_t value)
    {
        variable->Type = VariableType::UINT32;
        *reinterpret_cast<uint32_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, uint64_t value)
    {
        variable->Type = VariableType::UINT64;
        *reinterpret_cast<uint64_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, int8_t value)
    {
        variable->Type = VariableType::INT8;
        *reinterpret_cast<int8_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, int16_t value)
    {
        variable->Type = VariableType::INT16;
        *reinterpret_cast<int16_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, int32_t value)
    {
        variable->Type = VariableType::INT32;
        *reinterpret_cast<int32_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, int64_t value)
    {
        variable->Type = VariableType::INT64;
        *reinterpret_cast<int64_t *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, float value)
    {
        variable->Type = VariableType::FLOAT;
        *reinterpret_cast<float *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, double value)
    {
        variable->Type = VariableType::DOUBLE;
        *reinterpret_cast<double *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, bool value)
    {
        variable->Type = VariableType::BOOLEAN;
        *reinterpret_cast<bool *>(variable->Value) = value;
    }
    template<>
    void VariableSet(Variable *variable, Variable value)
    {
        variable->Type = value.Type;
        std::memcpy(variable->Value, &value.Value, sizeof(Variable::Value));
    }
}
#endif