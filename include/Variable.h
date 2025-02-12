#include <cstring>
#include <stdlib.h>
#include <type_traits>
#include "VariableType.h"

#ifndef VARIABLE_H
#define VARIABLE_H
namespace OperationArchitecture
{
    struct Variable;

    template<typename K>
    K VariableTo(const Variable *variable);
    template<typename K>
    void VariableSet(Variable *variable, K value);
    
    struct alignas(VARIABLE_ALIGN) Variable
    {
        union
        {
            uint8_t     ValueArray[VARIABLE_VALUE_SIZE] = {};
            uint8_t     UINT8Value;
            uint16_t    UINT16Value;
            uint32_t    UINT32Value;
            uint64_t    UINT64Value;
            int8_t      INT8Value;
            int16_t     INT16Value;
            int32_t     INT32Value;
            int64_t     INT64Value;
            float       FLOATValue;
            double      DOUBLEValue;
            bool        BOOLEANValue;
            struct{
                void*   POINTERValue;
                size_t  POINTERValueSize;
            };
        };
        VariableType Type;

        template<typename K>
        Variable(K variable)
        {
            VariableSet(this, variable);
        }

        Variable()
        {
            Type = VOID;
            for(size_t i = 0; i < sizeof(ValueArray); i++)
                ValueArray[i] = 0;
        }

        template<typename K>
        void operator=(K value)
        {
            VariableSet(this, value);
        }

        template<typename K>
        operator K() const { return VariableTo<K>(this); }

		size_t Size() const
		{
            if(Type == BIGOTHER || Type == POINTER)
                return POINTERValueSize;
            if(Type == OTHER)
                return ValueArray[VARIABLE_VALUE_SIZE-1];
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
            ret.INT64Value &= a.INT64Value;
            return ret;
        }
        Variable operator|(Variable a) const
        {
            if(Type == BIGOTHER || Type == OTHER || Type == POINTER ||
                a.Type == BIGOTHER || a.Type == OTHER || a.Type == POINTER)
                return static_cast<uint8_t>(0);

            Variable ret = *this;
            ret.INT64Value |= a.INT64Value;
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
//optimization screws this up. casting a uint64_t to a pointer is most likely undefined behavior
#pragma GCC push_options
#pragma GCC optimize("O0")
    template<typename K>
    inline K VariableTo(const Variable *variable)
    {
        switch(variable->Type)
        {
            case VariableType::BIGOTHER:
            case VariableType::POINTER:
                if(std::is_pointer<K>::value) //if typename is a pointer, return the pointer
                    return *reinterpret_cast<const K *>(&variable->POINTERValue);
                return *reinterpret_cast<const K *>(variable->POINTERValue); //otherwise, return the value stored in the pointer
            case VariableType::OTHER:
                if(std::is_pointer<K>::value) //if typename is a pointer, return the pointer
                {
                    //probably a better, 1 liner way to do this
                    const uint8_t *intermediatePointer = &variable->ValueArray[0];
                    return *reinterpret_cast<const K*>(reinterpret_cast<const void *>(&intermediatePointer));
                }
                return *reinterpret_cast<const K *>(&variable->ValueArray);
            case VariableType::VOID:
                return K();
            default: 
                return *reinterpret_cast<const K *>(&variable->ValueArray);
        }
    }
#pragma GCC pop_options
    template<typename K>
    inline const K VariableScalarTo(const Variable *variable)
    {
        switch(variable->Type)
        {
            case VariableType::UINT8: return static_cast<const K>(variable->UINT8Value);
            case VariableType::UINT16: return static_cast<const K>(variable->UINT16Value);
            case VariableType::UINT32: return static_cast<const K>(variable->UINT32Value);
            case VariableType::UINT64: return static_cast<const K>(variable->UINT64Value);
            case VariableType::INT8: if(static_cast<const K>(-1) > 0 && variable->INT8Value < 0) return 0; return static_cast<const K>(variable->INT8Value);
            case VariableType::INT16: if(static_cast<const K>(-1) > 0 && variable->INT16Value < 0) return 0; return static_cast<const K>(variable->INT16Value);
            case VariableType::INT32: if(static_cast<const K>(-1) > 0 && variable->INT32Value < 0) return 0; return static_cast<const K>(variable->INT32Value);
            case VariableType::INT64: if(static_cast<const K>(-1) > 0 && variable->INT64Value < 0) return 0; return static_cast<const K>(variable->INT64Value);
            case VariableType::FLOAT: if(static_cast<const K>(-1) > 0 && variable->FLOATValue < 0) return 0; return static_cast<const K>(variable->FLOATValue);
            case VariableType::DOUBLE: if(static_cast<const K>(-1) > 0 && variable->DOUBLEValue < 0) return 0; return static_cast<const K>(variable->DOUBLEValue);
            case VariableType::BOOLEAN: return static_cast<const K>(variable->BOOLEANValue);
            default:
                return 0;
        }
    }
    template<>
    inline uint8_t VariableTo<uint8_t>(const Variable *variable)  { return VariableScalarTo<uint8_t>(variable); }
    template<>
    inline uint16_t VariableTo<uint16_t>(const Variable *variable) { return VariableScalarTo<uint16_t>(variable); }
    template<>
    inline uint32_t VariableTo<uint32_t>(const Variable *variable) { return VariableScalarTo<uint32_t>(variable); }
    template<>
    inline uint64_t VariableTo<uint64_t>(const Variable *variable) { return VariableScalarTo<uint64_t>(variable); }
    template<>
    inline int8_t VariableTo<int8_t>(const Variable *variable) { return VariableScalarTo<int8_t>(variable); }
    template<>
    inline int16_t VariableTo<int16_t>(const Variable *variable) { return VariableScalarTo<int16_t>(variable); }
    template<>
    inline int32_t VariableTo<int32_t>(const Variable *variable) { return VariableScalarTo<int32_t>(variable); }
    template<>
    inline int64_t VariableTo<int64_t>(const Variable *variable) { return VariableScalarTo<int64_t>(variable); }
    template<>
    inline float VariableTo<float>(const Variable *variable) { return VariableScalarTo<float>(variable); }
    template<>
    inline double VariableTo<double>(const Variable *variable) { return VariableScalarTo<double>(variable); }
    template<>
    inline bool VariableTo<bool>(const Variable *Variable)
    {
        if(Variable->Type == VariableType::BOOLEAN)
            return Variable->BOOLEANValue;
        return false;
    }
    template<>
    inline Variable VariableTo<Variable>(const Variable *variable) { return *variable; }

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
    
    template<typename K>
    inline void VariableSet(Variable *variable, K value)
    {
        if(sizeof(value) > VARIABLE_VALUE_SIZE - 1)
        {
            if(variable->Type != VariableType::BIGOTHER)
            {
                void * dyn = malloc(sizeof(value));
                variable->POINTERValue = dyn;
                variable->POINTERValueSize = sizeof(value);
            }
            if(variable->POINTERValueSize != sizeof(value))
            {
                free(variable->POINTERValue);
                void * dyn = malloc(sizeof(value));
                variable->POINTERValue = dyn;
                variable->POINTERValueSize = sizeof(value);
            }
            variable->Type = VariableType::BIGOTHER;
            std::memcpy(variable->POINTERValue, &value, sizeof(K));
        }
        else
        {
            if(variable->Type == VariableType::BIGOTHER)
            {
                free(variable->POINTERValue);
            }
            if(std::is_pointer<K>::value)
            {
                variable->Type = VariableType::POINTER;
                *reinterpret_cast<K *>(variable->ValueArray) = value;
                variable->POINTERValueSize = size_of<K>::value;
            }
            else
            {
                variable->Type = VariableType::OTHER;
                *reinterpret_cast<K *>(variable->ValueArray) = value;
                variable->ValueArray[VARIABLE_VALUE_SIZE - 1] = sizeof(value);
            }
        }
    }
    template<>
    inline void VariableSet(Variable *variable, uint8_t value)
    {
        variable->Type = VariableType::UINT8;
        variable->UINT8Value = value;
    }
    template<>
    inline void VariableSet(Variable *variable, uint16_t value)
    {
        variable->Type = VariableType::UINT16;
        variable->UINT16Value = value;
    }
    template<>
    inline void VariableSet(Variable *variable, uint32_t value)
    {
        variable->Type = VariableType::UINT32;
        variable->UINT32Value = value;
    }
    template<>
    inline void VariableSet(Variable *variable, uint64_t value)
    {
        variable->Type = VariableType::UINT64;
        variable->UINT64Value = value;
    }
    template<>
    inline void VariableSet(Variable *variable, int8_t value)
    {
        variable->Type = VariableType::INT8;
        variable->INT8Value = value;
    }
    template<>
    inline void VariableSet(Variable *variable, int16_t value)
    {
        variable->Type = VariableType::INT16;
        variable->INT16Value = value;
    }
    template<>
    inline void VariableSet(Variable *variable, int32_t value)
    {
        variable->Type = VariableType::INT32;
        variable->INT32Value = value;
    }
    template<>
    inline void VariableSet(Variable *variable, int64_t value)
    {
        variable->Type = VariableType::INT64;
        variable->INT64Value = value;
    }
    template<>
    inline void VariableSet(Variable *variable, float value)
    {
        variable->Type = VariableType::FLOAT;
        variable->FLOATValue = value;
    }
    template<>
    inline void VariableSet(Variable *variable, double value)
    {
        variable->Type = VariableType::DOUBLE;
        variable->DOUBLEValue = value;
    }
    template<>
    inline void VariableSet(Variable *variable, bool value)
    {
        variable->Type = VariableType::BOOLEAN;
        variable->BOOLEANValue = value;
    }
    template<>
    inline void VariableSet(Variable *variable, Variable value)
    {
        variable->Type = value.Type;
        std::memcpy(variable->ValueArray, &value.ValueArray, sizeof(Variable::ValueArray));
    }
}
#endif