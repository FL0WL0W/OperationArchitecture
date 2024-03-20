#include <cstring>
#include <stdlib.h>
#include <type_traits>
#include "VariableType.h"

#ifndef VARIABLE_H
#define VARIABLE_H
namespace OperationArchitecture
{
    template<bool b, typename K2>
    struct size_of2 { const static size_t value = sizeof(K2); };

    template<typename K2>
    struct size_of2<true, K2> { const static K2 k; const static size_t value = sizeof(*k); };

    template<>
    struct size_of2<true, const void *> { const static size_t value = 0; };

    template<>
    struct size_of2<true, void *> { const static size_t value = 0; };

    template<typename K>
    struct size_of 
    {
        const static size_t value = size_of2<std::is_pointer<K>::value, K>::value;
    };

    struct alignas(VARIABLE_ALIGN) VariableBase
    {
        uint8_t Value[VARIABLE_VALUE_SIZE];
        VariableType Type;
    };
    struct Variable;

    template<typename K>
    const K VariableBaseTo(const VariableBase *variable)
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
//optimization screws this up. casting a uint64_t to a pointer is most likely undefined behavior
#pragma GCC push_options
#pragma GCC optimize("O0")
    template<typename K>
    K VariableTo(const VariableBase *variable)
    {
        switch(variable->Type)
        {
            case VariableType::BIGOTHER:
            case VariableType::POINTER:
                if(std::is_pointer<K>::value) //if typename is a pointer, return the pointer
                    return *reinterpret_cast<const K *>(variable->Value);
                return **reinterpret_cast<K * const *>(variable->Value); //otherwise, return the value stored in the pointer
            case VariableType::OTHER:
                if(std::is_pointer<K>::value) //if typename is a pointer, return the pointer 
                {
                    //probably a better, 1 liner way to do this
                    const uint8_t *intermediatePointer = &variable->Value[0];
                    return *reinterpret_cast<const K*>(reinterpret_cast<const void *>(&intermediatePointer));
                }
                return *reinterpret_cast<const K *>(variable->Value);
            case VariableType::VOID:
                return K();
            default: 
                return *reinterpret_cast<const K *>(variable->Value);
        }
    }
#pragma GCC pop_options
    template<>
    uint8_t VariableTo<uint8_t>(const VariableBase *variable);
    template<>
    uint16_t VariableTo<uint16_t>(const VariableBase *variable);
    template<>
    uint32_t VariableTo<uint32_t>(const VariableBase *variable);
    template<>
    uint64_t VariableTo<uint64_t>(const VariableBase *variable);
    template<>
    int8_t VariableTo<int8_t>(const VariableBase *variable);
    template<>
    int16_t VariableTo<int16_t>(const VariableBase *variable);
    template<>
    int32_t VariableTo<int32_t>(const VariableBase *variable);
    template<>
    int64_t VariableTo<int64_t>(const VariableBase *variable);
    template<>
    float VariableTo<float>(const VariableBase *variable);
    template<>
    double VariableTo<double>(const VariableBase *variable);
    template<>
    bool VariableTo<bool>(const VariableBase *variable);
    template<>
    VariableBase VariableTo<VariableBase>(const VariableBase *variable);
    template<>
    Variable VariableTo<Variable>(const VariableBase *variable);

    template<typename K>
    void VariableSet(VariableBase *variable, K value)
    {
        if(sizeof(value) > VARIABLE_VALUE_SIZE - 1)
        {
            if(variable->Type != VariableType::BIGOTHER)
            {
                void * dyn = malloc(sizeof(value));
                *reinterpret_cast<void **>(variable->Value) = dyn;
                *reinterpret_cast<size_t *>(reinterpret_cast<void **>(variable->Value) + 1) = sizeof(value);
            }
            if(*reinterpret_cast<size_t *>(reinterpret_cast<void **>(variable->Value) + 1) != sizeof(value))
            {
                free(*reinterpret_cast<void **>(variable->Value));
                void * dyn = malloc(sizeof(value));
                *reinterpret_cast<void **>(variable->Value) = dyn;
                *reinterpret_cast<size_t *>(reinterpret_cast<void **>(variable->Value) + 1) = sizeof(value);
            }
            variable->Type = VariableType::BIGOTHER;
            std::memcpy(*reinterpret_cast<K **>(variable->Value), &value, sizeof(K));
        }
        else
        {
            if(variable->Type == VariableType::BIGOTHER)
            {
                free(*reinterpret_cast<void **>(variable->Value));
            }
            if(std::is_pointer<K>::value)
            {
                variable->Type = VariableType::POINTER;
                *reinterpret_cast<K *>(variable->Value) = value;
                *reinterpret_cast<size_t *>(reinterpret_cast<void **>(variable->Value) + 1) = size_of<K>::value;
            }
            else
            {
                variable->Type = VariableType::OTHER;
                *reinterpret_cast<K *>(variable->Value) = value;
                variable->Value[VARIABLE_VALUE_SIZE - 1] = sizeof(value);
            }
        }
    }
    template<>
    void VariableSet<uint8_t>(VariableBase *variable, uint8_t value);
    template<>
    void VariableSet<uint16_t>(VariableBase *variable, uint16_t value);
    template<>
    void VariableSet<uint32_t>(VariableBase *variable, uint32_t value);
    template<>
    void VariableSet<uint64_t>(VariableBase *variable, uint64_t value);
    template<>
    void VariableSet<int8_t>(VariableBase *variable, int8_t value);
    template<>
    void VariableSet<int16_t>(VariableBase *variable, int16_t value);
    template<>
    void VariableSet<int32_t>(VariableBase *variable, int32_t value);
    template<>
    void VariableSet<int64_t>(VariableBase *variable, int64_t value);
    template<>
    void VariableSet<float>(VariableBase *variable, float value);
    template<>
    void VariableSet<double>(VariableBase *variable, double value);
    template<>
    void VariableSet<bool>(VariableBase *variable, bool value);
    template<>
    void VariableSet<VariableBase>(VariableBase *variable, VariableBase value);
    template<>
    void VariableSet<Variable>(VariableBase *variable, Variable value);

    struct Variable : public VariableBase
    {
        template<typename K>
        Variable(K variable)
        {
            VariableSet(this, variable);
        }

        Variable()
        {
            Type = VOID;
            for(size_t i = 0; i < sizeof(Value); i++)
                Value[i] = 0;
        }

        template<typename K>
        Variable operator=(K value)
        {
            VariableSet(this, value);
            return *this;
        }

        template<typename K>
        operator K() const { return VariableTo<K>(this); }

		size_t Size() const
		{
            if(Type == BIGOTHER || Type == POINTER)
                return *reinterpret_cast<const size_t *>(reinterpret_cast<void * const *>(Value) + 1);
            if(Type == OTHER)
                return Value[VARIABLE_VALUE_SIZE-1];
			return VariableTypeSizeOf(Type);
		}

        static Variable Int64ToVariable(int64_t result, VariableType targetType)
        {
            switch(targetType)
            {
                case UINT8:
                    if(result > static_cast<int64_t>(4294967295))
                        return static_cast<uint64_t>(result);
                    if(result > 65535)
                        return static_cast<uint32_t>(result);
                    if(result > 255)
                        return static_cast<uint16_t>(result);
                    if(result < -static_cast<int64_t>(2147483648))
                        return static_cast<int64_t>(result);
                    if(result < -32768)
                        return static_cast<int32_t>(result);
                    if(result < -128)
                        return static_cast<int16_t>(result);
                    if(result < 0)
                        return static_cast<int8_t>(result);
                    return static_cast<uint8_t>(result);
                case INT8:
                    if(result > static_cast<int64_t>(2147483648) || result < -static_cast<int64_t>(2147483648))
                        return result;
                    if(result > 32767 || result < -32768)
                        return static_cast<int32_t>(result);
                    if(result > 127 || result < -128)
                        return static_cast<int16_t>(result);
                    return static_cast<int8_t>(result);
                case UINT16:
                    if(result > static_cast<int64_t>(4294967295))
                        return static_cast<uint64_t>(result);
                    if(result < -static_cast<int64_t>(2147483648))
                        return static_cast<int64_t>(result);
                    if(result > 65535)
                        return static_cast<uint32_t>(result);
                    if(result < -32768)
                        return static_cast<int32_t>(result);
                    if(result < 0)
                        return static_cast<int16_t>(result);
                    return static_cast<uint16_t>(result);
                case INT16:
                    if(result > static_cast<int64_t>(2147483648) || result < -static_cast<int64_t>(2147483648))
                        return result;
                    if(result > 32767 || result < -32768)
                        return static_cast<int32_t>(result);
                    return static_cast<int16_t>(result);
                case UINT32:
                    if(result > static_cast<int64_t>(4294967295))
                        return static_cast<uint64_t>(result);
                    if(result < -static_cast<int64_t>(2147483648))
                        return static_cast<int64_t>(result);
                    if(result < 0)
                        return static_cast<int32_t>(result);
                    return static_cast<uint32_t>(result);
                case INT32:
                    if(result > static_cast<int64_t>(2147483648) || result < -static_cast<int64_t>(2147483648))
                        return result;
                    return static_cast<int32_t>(result);
                case UINT64:
                    if(result < 0)
                        return static_cast<int64_t>(result);
                    return static_cast<uint64_t>(result);
                case INT64:
                    return result;
                default:
                    return Variable();//its bad if this happens
            }
        }

        Variable operator+(Variable a) const
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return static_cast<bool>(*this) || static_cast<bool>(a);
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return static_cast<double>(*this) + static_cast<double>(a);
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return static_cast<float>(*this) + static_cast<float>(a);
            }
            uint64_t preResult = static_cast<uint64_t>(*this) + static_cast<uint64_t>(a);
            if(preResult > 9223372036854775807)
                return static_cast<uint64_t>(preResult);
            int64_t result = static_cast<int64_t>(*this) + static_cast<int64_t>(a);
            return Int64ToVariable(result, Type);
        }
        Variable operator-(Variable a) const
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return static_cast<bool>(*this) || !static_cast<bool>(a);
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return static_cast<double>(*this) - static_cast<double>(a);
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return static_cast<float>(*this) - static_cast<float>(a);
            }
            if(static_cast<uint64_t>(*this) > static_cast<uint64_t>(a))
            {
                uint64_t preResult = static_cast<uint64_t>(*this) - static_cast<uint64_t>(a);
                if(preResult > 9223372036854775807)
                    return static_cast<uint64_t>(preResult);
            }
            int64_t result = static_cast<int64_t>(*this) - static_cast<int64_t>(a);
            return Int64ToVariable(result, Type);
        }
        Variable operator*(Variable a) const
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return static_cast<bool>(*this) && static_cast<bool>(a);
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return static_cast<double>(*this) * static_cast<double>(a);
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return static_cast<float>(*this) * static_cast<float>(a);
            }
            uint64_t preResult = static_cast<uint64_t>(*this) * static_cast<uint64_t>(a);
            if(preResult > 9223372036854775807)
                return static_cast<uint64_t>(preResult);
            int64_t result = static_cast<int64_t>(*this) * static_cast<int64_t>(a);
            return Int64ToVariable(result, Type);
        }
        Variable operator/(Variable a) const
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return static_cast<bool>(*this) && !static_cast<bool>(a);
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return static_cast<double>(*this) / static_cast<double>(a);
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return static_cast<float>(*this) / static_cast<float>(a);
            }
            if(static_cast<uint64_t>(a) != 0)
            {
                uint64_t preResult = static_cast<uint64_t>(*this) / static_cast<uint64_t>(a);
                if(preResult > 9223372036854775807)
                    return static_cast<uint64_t>(preResult);
            }
            if(static_cast<int64_t>(a) == 0)
                return false;
            int64_t result = static_cast<int64_t>(*this) / static_cast<int64_t>(a);
            return Int64ToVariable(result, Type);
        }
        Variable operator&(Variable a) const
        {
            if(Type == BIGOTHER || Type == OTHER || Type == POINTER ||
                a.Type == BIGOTHER || a.Type == OTHER || a.Type == POINTER)
                return static_cast<uint8_t>(0);
            
            Variable ret = *this;
            *reinterpret_cast<int64_t *>(&ret.Value) &= *reinterpret_cast<int64_t *>(&a.Value);
            return ret;
        }
        Variable operator|(Variable a) const
        {
            if(Type == BIGOTHER || Type == OTHER || Type == POINTER ||
                a.Type == BIGOTHER || a.Type == OTHER || a.Type == POINTER)
                return static_cast<uint8_t>(0);

            Variable ret = *this;
            *reinterpret_cast<int64_t *>(&ret.Value) |= *reinterpret_cast<int64_t *>(&a.Value);
            return ret;
        }
        bool operator==(Variable a) const
        {
            if(Type == DOUBLE || a.Type == DOUBLE)
                return static_cast<double>(*this) == static_cast<double>(a);
            if(Type == FLOAT || a.Type == FLOAT)
                return static_cast<float>(*this) == static_cast<float>(a);
            if(Type == UINT64 && a.Type == UINT64)
                return static_cast<uint64_t>(*this) == static_cast<uint64_t>(a);
            if(Type == UINT64 && static_cast<uint64_t>(*this) > 9223372036854775807)
                return false;
            if(a.Type == UINT64 && static_cast<uint64_t>(a) > 9223372036854775807)
                return false;
            if(Type == BOOLEAN || a.Type == BOOLEAN)
                return static_cast<bool>(*this) == static_cast<bool>(a);
            return static_cast<int64_t>(*this) == static_cast<int64_t>(a);
        }
        bool operator<(Variable a) const
        {
            if(Type == DOUBLE || a.Type == DOUBLE)
                return static_cast<double>(*this) < static_cast<double>(a);
            if(Type == FLOAT || a.Type == FLOAT)
                return static_cast<float>(*this) < static_cast<float>(a);
            if(Type == UINT64 && a.Type == UINT64)
                return static_cast<uint64_t>(*this) < static_cast<uint64_t>(a);
            if(Type == UINT64 && static_cast<uint64_t>(*this) >= 9223372036854775807)
                return false;
            if(a.Type == UINT64 && static_cast<uint64_t>(a) >= 9223372036854775807)
                return true;
            if(Type == BOOLEAN || a.Type == BOOLEAN)
                return static_cast<bool>(0);
            return static_cast<int64_t>(*this) < static_cast<int64_t>(a);
        }
        bool operator>(Variable a) const
        {
            return a < *this;
        }
        bool operator>=(Variable a) const
        {
            return !(*this < a);
        }
        bool operator<=(Variable a) const
        {
            return !(a < *this);
        }
    };
}
#endif