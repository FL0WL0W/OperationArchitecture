#include <cstring>
#include <stdlib.h>
#include <type_traits>
#include "VariableType.h"

#ifndef VARIABLE_H
#define VARIABLE_H
namespace OperationArchitecture
{
    struct alignas(VARIABLE_ALIGN) VariableBase
    {
        uint8_t Value[VARIABLE_VALUE_SIZE];
        VariableType Type;
    };
    struct Variable;

    template<typename K>
    K VariableBaseTo(VariableBase *variable)
    {
        switch(variable->Type)
        {
            case VariableType::UINT8: return static_cast<K>(*reinterpret_cast<uint8_t *>(variable->Value));
            case VariableType::UINT16: return static_cast<K>(*reinterpret_cast<uint16_t *>(variable->Value));
            case VariableType::UINT32: return static_cast<K>(*reinterpret_cast<uint32_t *>(variable->Value));
            case VariableType::UINT64: return static_cast<K>(*reinterpret_cast<uint64_t *>(variable->Value));
            case VariableType::INT8: if(static_cast<K>(-1) > 0 && *reinterpret_cast<int8_t *>(variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<int8_t *>(variable->Value));
            case VariableType::INT16: if(static_cast<K>(-1) > 0 && *reinterpret_cast<int16_t *>(variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<int16_t *>(variable->Value));
            case VariableType::INT32: if(static_cast<K>(-1) > 0 && *reinterpret_cast<int32_t *>(variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<int32_t *>(variable->Value));
            case VariableType::INT64: if(static_cast<K>(-1) > 0 && *reinterpret_cast<int64_t *>(variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<int64_t *>(variable->Value));
            case VariableType::FLOAT: if(static_cast<K>(-1) > 0 && *reinterpret_cast<float *>(variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<float *>(variable->Value));
            case VariableType::DOUBLE: if(static_cast<K>(-1) > 0 && *reinterpret_cast<double *>(variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<double *>(variable->Value));
            case VariableType::BOOLEAN: return static_cast<K>(*reinterpret_cast<bool *>(variable->Value));
            default:
                return 0;
        }
    }
//optimization screws this up. casting a uint64_t to a pointer is most likely undefined behavior
#pragma GCC push_options
#pragma GCC optimize("O0")
    template<typename K>
    K VariableTo(VariableBase *variable)
    {
        switch(variable->Type)
        {
            case VariableType::BIGOTHER:
            case VariableType::POINTER:
                if(std::is_pointer<K>::value) //if typename is a pointer, return the pointer
                    return *reinterpret_cast<K *>(variable->Value);
                return **reinterpret_cast<K **>(variable->Value); //otherwise, return the value stored in the pointer
            case VariableType::OTHER:
                return *reinterpret_cast<K *>(variable->Value);
            default: 
                //this is bad 
                return *reinterpret_cast<K *>(0);
        }
    }
#pragma GCC pop_options
    template<>
    uint8_t VariableTo<uint8_t>(VariableBase *variable);
    template<>
    uint16_t VariableTo<uint16_t>(VariableBase *variable);
    template<>
    uint32_t VariableTo<uint32_t>(VariableBase *variable);
    template<>
    uint64_t VariableTo<uint64_t>(VariableBase *variable);
    template<>
    int8_t VariableTo<int8_t>(VariableBase *variable);
    template<>
    int16_t VariableTo<int16_t>(VariableBase *variable);
    template<>
    int32_t VariableTo<int32_t>(VariableBase *variable);
    template<>
    int64_t VariableTo<int64_t>(VariableBase *variable);
    template<>
    float VariableTo<float>(VariableBase *variable);
    template<>
    double VariableTo<double>(VariableBase *variable);
    template<>
    bool VariableTo<bool>(VariableBase *variable);
    template<>
    VariableBase VariableTo<VariableBase>(VariableBase *variable);
    template<>
    Variable VariableTo<Variable>(VariableBase *variable);

    template<typename K>
    void VariableSet(VariableBase *variable, K value)
    {
        if(sizeof(K) > VARIABLE_VALUE_SIZE)
        {
            if(variable->Type != VariableType::BIGOTHER)
            {
                void * dyn = malloc(sizeof(K));
                *reinterpret_cast<void **>(variable->Value) = dyn;
                *reinterpret_cast<size_t *>(reinterpret_cast<void **>(variable->Value) + 1) = sizeof(K);
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
            }
            else
            {
                variable->Type = VariableType::OTHER;
                *reinterpret_cast<K *>(variable->Value) = value;
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
        Variable()
        {
            Type = VOID;
            for(size_t i = 0; i < sizeof(Value); i++)
                Value[i] = 0;
        }
        Variable(VariableBase variable) { Set(variable); }
        Variable(uint8_t variable) { Set(variable); }
        Variable(uint16_t variable) { Set(variable); }
        Variable(uint32_t variable) { Set(variable); }
        Variable(uint64_t variable) { Set(variable); }
        Variable(int8_t variable) { Set(variable); }
        Variable(int16_t variable) { Set(variable); }
        Variable(int32_t variable) { Set(variable); }
        Variable(int64_t variable) { Set(variable); }
        Variable(float variable) { Set(variable); }
        Variable(double variable) { Set(variable); }
        Variable(bool variable) { Set(variable); }

        template<typename K>
        static Variable Create(K value) 
        { 
            Variable variable;
            variable.Set(value); 
            return variable;
        }

        template<typename K>
        void Set(K value)
        {
            VariableSet(this, value);
        }

        template<typename K>
        K To()
        {
            return VariableTo<K>(this);
        }

		size_t Size() const
		{
            if(Type == VariableType::BIGOTHER)
                return *reinterpret_cast<const size_t *>(reinterpret_cast<void * const *>(Value) + 1);
			return VariableTypeSizeOf(Type);
		}

        static Variable Int64ToVariable(int64_t result, VariableType targetType)
        {
            switch(targetType)
            {
                case UINT8:
                    if(result > static_cast<int64_t>(4294967295))
                        return Create(static_cast<uint64_t>(result));
                    if(result > 65535)
                        return Create(static_cast<uint32_t>(result));
                    if(result > 255)
                        return Create(static_cast<uint16_t>(result));
                    if(result < -static_cast<int64_t>(2147483648))
                        return Create(static_cast<int64_t>(result));
                    if(result < -32768)
                        return Create(static_cast<int32_t>(result));
                    if(result < -128)
                        return Create(static_cast<int16_t>(result));
                    if(result < 0)
                        return Create(static_cast<int8_t>(result));
                    return Create(static_cast<uint8_t>(result));
                case INT8:
                    if(result > static_cast<int64_t>(2147483648) || result < -static_cast<int64_t>(2147483648))
                        return Create(result);
                    if(result > 32767 || result < -32768)
                        return Create(static_cast<int32_t>(result));
                    if(result > 127 || result < -128)
                        return Create(static_cast<int16_t>(result));
                    return Create(static_cast<int8_t>(result));
                case UINT16:
                    if(result > static_cast<int64_t>(4294967295))
                        return Create(static_cast<uint64_t>(result));
                    if(result < -static_cast<int64_t>(2147483648))
                        return Create(static_cast<int64_t>(result));
                    if(result > 65535)
                        return Create(static_cast<uint32_t>(result));
                    if(result < -32768)
                        return Create(static_cast<int32_t>(result));
                    if(result < 0)
                        return Create(static_cast<int16_t>(result));
                    return Create(static_cast<uint16_t>(result));
                case INT16:
                    if(result > static_cast<int64_t>(2147483648) || result < -static_cast<int64_t>(2147483648))
                        return Create(result);
                    if(result > 32767 || result < -32768)
                        return Create(static_cast<int32_t>(result));
                    return Create(static_cast<int16_t>(result));
                case UINT32:
                    if(result > static_cast<int64_t>(4294967295))
                        return Create(static_cast<uint64_t>(result));
                    if(result < -static_cast<int64_t>(2147483648))
                        return Create(static_cast<int64_t>(result));
                    if(result < 0)
                        return Create(static_cast<int32_t>(result));
                    return Create(static_cast<uint32_t>(result));
                case INT32:
                    if(result > static_cast<int64_t>(2147483648) || result < -static_cast<int64_t>(2147483648))
                        return Create(result);
                    return Create(static_cast<int32_t>(result));
                case UINT64:
                    if(result < 0)
                        return Create(static_cast<int64_t>(result));
                    return Create(static_cast<uint64_t>(result));
                case INT64:
                    return Create(result);
                default:
                    return Variable();//its bad if this happens
            }
        }

        Variable operator+(Variable a)
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return Create(To<bool>() || a.To<bool>());
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return Create(To<double>() + a.To<double>());
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return Create(To<float>() + a.To<float>());
            }
            uint64_t preResult = To<uint64_t>() + a.To<uint64_t>();
            if(preResult > 9223372036854775807)
                return Create(static_cast<uint64_t>(preResult));
            int64_t result = To<int64_t>() + a.To<int64_t>();
            return Int64ToVariable(result, Type);
        }
        Variable operator-(Variable a)
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return Create(To<bool>() || !a.To<bool>());
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return Create(To<double>() - a.To<double>());
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return Create(To<float>() - a.To<float>());
            }
            if(To<uint64_t>() > a.To<uint64_t>())
            {
                uint64_t preResult = To<uint64_t>() - a.To<uint64_t>();
                if(preResult > 9223372036854775807)
                    return Create(static_cast<uint64_t>(preResult));
            }
            int64_t result = To<int64_t>() - a.To<int64_t>();
            return Int64ToVariable(result, Type);
        }
        Variable operator*(Variable a)
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return Create(To<bool>() && a.To<bool>());
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return Create(To<double>() * a.To<double>());
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return Create(To<float>() * a.To<float>());
            }
            uint64_t preResult = To<uint64_t>() * a.To<uint64_t>();
            if(preResult > 9223372036854775807)
                return Create(static_cast<uint64_t>(preResult));
            int64_t result = To<int64_t>() * a.To<int64_t>();
            return Int64ToVariable(result, Type);
        }
        Variable operator/(Variable a)
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return Create(To<bool>() && !a.To<bool>());
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return Create(To<double>() / a.To<double>());
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return Create(To<float>() / a.To<float>());
            }
            if(a.To<uint64_t>() != 0)
            {
                uint64_t preResult = To<uint64_t>() / a.To<uint64_t>();
                if(preResult > 9223372036854775807)
                    return Create(static_cast<uint64_t>(preResult));
            }
            if(a.To<int64_t>() == 0)
                return Create(false);
            int64_t result = To<int64_t>() / a.To<int64_t>();
            return Int64ToVariable(result, Type);
        }
        Variable operator&(Variable a)
        {
            if(Type == BIGOTHER || Type == OTHER || Type == POINTER ||
                a.Type == BIGOTHER || a.Type == OTHER || a.Type == POINTER)
                return 0;
            
            Variable ret = *this;
            *reinterpret_cast<int64_t *>(&ret.Value) &= *reinterpret_cast<int64_t *>(&a.Value);
            return ret;
        }
        Variable operator|(Variable a)
        {
            if(Type == BIGOTHER || Type == OTHER || Type == POINTER ||
                a.Type == BIGOTHER || a.Type == OTHER || a.Type == POINTER)
                return 0;

            Variable ret = *this;
            *reinterpret_cast<int64_t *>(&ret.Value) |= *reinterpret_cast<int64_t *>(&a.Value);
            return ret;
        }
        bool operator==(Variable a)
        {
            if(Type == DOUBLE || a.Type == DOUBLE)
                return To<double>() == a.To<double>();
            if(Type == FLOAT || a.Type == FLOAT)
                return To<float>() == a.To<float>();
            if(Type == UINT64 && a.Type == UINT64)
                return To<uint64_t>() == a.To<uint64_t>();
            if(Type == UINT64 && To<uint64_t>() > 9223372036854775807)
                return false;
            if(a.Type == UINT64 && a.To<uint64_t>() > 9223372036854775807)
                return false;
            if(Type == BOOLEAN || a.Type == BOOLEAN)
                return To<bool>() == a.To<bool>();
            return To<int64_t>() == a.To<int64_t>();
        }
        bool operator<(Variable a)
        {
            if(Type == DOUBLE || a.Type == DOUBLE)
                return To<double>() < a.To<double>();
            if(Type == FLOAT || a.Type == FLOAT)
                return To<float>() < a.To<float>();
            if(Type == UINT64 && a.Type == UINT64)
                return To<uint64_t>() < a.To<uint64_t>();
            if(Type == UINT64 && To<uint64_t>() >= 9223372036854775807)
                return false;
            if(a.Type == UINT64 && a.To<uint64_t>() >= 9223372036854775807)
                return true;
            if(Type == BOOLEAN || a.Type == BOOLEAN)
                return static_cast<bool>(0);
            return To<int64_t>() < a.To<int64_t>();
        }
        bool operator>(Variable a)
        {
            return a < *this;
        }
        bool operator>=(Variable a)
        {
            return !(*this < a);
        }
        bool operator<=(Variable a)
        {
            return !(a < *this);
        }
    };
}
#endif