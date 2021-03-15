#include <stdint.h>
#include "VariableType.h"

#ifndef VARIABLE_H
#define VARIABLE_H
namespace OperationArchitecture
{
    struct VariableBase
    {
        VariableType Type;
        uint64_t Value;
    };

    template<typename K>
    K VariableBaseTo(VariableBase *variable)
    {
        switch(variable->Type)
        {
            case VariableType::UINT8: return static_cast<K>(*reinterpret_cast<uint8_t *>(&variable->Value));
            case VariableType::UINT16: return static_cast<K>(*reinterpret_cast<uint16_t *>(&variable->Value));
            case VariableType::UINT32: return static_cast<K>(*reinterpret_cast<uint32_t *>(&variable->Value));
            case VariableType::UINT64: return static_cast<K>(*reinterpret_cast<uint64_t *>(&variable->Value));
            case VariableType::INT8: if(static_cast<K>(-1) > 0 && *reinterpret_cast<int8_t *>(&variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<int8_t *>(&variable->Value));
            case VariableType::INT16: if(static_cast<K>(-1) > 0 && *reinterpret_cast<int16_t *>(&variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<int16_t *>(&variable->Value));
            case VariableType::INT32: if(static_cast<K>(-1) > 0 && *reinterpret_cast<int32_t *>(&variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<int32_t *>(&variable->Value));
            case VariableType::INT64: if(static_cast<K>(-1) > 0 && *reinterpret_cast<int64_t *>(&variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<int64_t *>(&variable->Value));
            case VariableType::FLOAT: if(static_cast<K>(-1) > 0 && *reinterpret_cast<float *>(&variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<float *>(&variable->Value));
            case VariableType::DOUBLE: if(static_cast<K>(-1) > 0 && *reinterpret_cast<double *>(&variable->Value) < 0) return 0; return static_cast<K>(*reinterpret_cast<double *>(&variable->Value));
            case VariableType::BOOLEAN: return static_cast<K>(*reinterpret_cast<bool *>(&variable->Value));
        }
        return 0;
    }
    template<typename K>
    K VariableTo(VariableBase *variable)
    {
        switch(variable->Type)
        {
            default: 
                break;
                //this is bad 
        }
        return 0;
    }
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

    struct Variable : public VariableBase
    {
        Variable()
        {
            Set(static_cast<uint8_t>(0));
        }
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
        Variable(void * variable) { Set(variable); }

        void Set(uint8_t variable)
        {
            Type = VariableType::UINT8;
            Value = *reinterpret_cast<uint64_t *>(&variable);
        }
        void Set(uint16_t variable)
        {
            Type = VariableType::UINT16;
            Value = *reinterpret_cast<uint64_t *>(&variable);
        }
        void Set(uint32_t variable)
        {
            Type = VariableType::UINT32;
            Value = *reinterpret_cast<uint64_t *>(&variable);
        }
        void Set(uint64_t variable)
        {
            Type = VariableType::UINT64;
            Value = *reinterpret_cast<uint64_t *>(&variable);
        }
        void Set(int8_t variable)
        {
            Type = VariableType::INT8;
            Value = *reinterpret_cast<uint64_t *>(&variable);
        }
        void Set(int16_t variable)
        {
            Type = VariableType::INT16;
            Value = *reinterpret_cast<uint64_t *>(&variable);
        }
        void Set(int32_t variable)
        {
            Type = VariableType::INT32;
            Value = *reinterpret_cast<uint64_t *>(&variable);
        }
        void Set(int64_t variable)
        {
            Type = VariableType::INT64;
            Value = *reinterpret_cast<uint64_t *>(&variable);
        }
        void Set(float variable)
        {
            Type = VariableType::FLOAT;
            Value = *reinterpret_cast<uint64_t *>(&variable);
        }
        void Set(double variable)
        {
            Type = VariableType::DOUBLE;
            Value = *reinterpret_cast<uint64_t *>(&variable);
        }
        void Set(bool variable)
        {
            Type = VariableType::BOOLEAN;
            Value = variable;
        }
        void Set(Variable variable)
        {
            Type = variable.Type;
            Value = variable.Value;
        }

        template<typename K>
        K To()
        {
            return VariableTo<K>(this);
        }

        static Variable Int64ToVariable(int64_t result, VariableType targetType)
        {
            switch(targetType)
            {
                case UINT8:
                    if(result > static_cast<int64_t>(4294967295))
                        return Variable(static_cast<uint64_t>(result));
                    if(result > 65535)
                        return Variable(static_cast<uint32_t>(result));
                    if(result > 255)
                        return Variable(static_cast<uint16_t>(result));
                    if(result < -static_cast<int64_t>(2147483648))
                        return Variable(static_cast<int64_t>(result));
                    if(result < -32768)
                        return Variable(static_cast<int32_t>(result));
                    if(result < -128)
                        return Variable(static_cast<int16_t>(result));
                    if(result < 0)
                        return Variable(static_cast<int8_t>(result));
                    return Variable(static_cast<uint8_t>(result));
                case INT8:
                    if(result > static_cast<int64_t>(2147483648) || result < -static_cast<int64_t>(2147483648))
                        return Variable(result);
                    if(result > 32767 || result < -32768)
                        return Variable(static_cast<int32_t>(result));
                    if(result > 127 || result < -128)
                        return Variable(static_cast<int16_t>(result));
                    return Variable(static_cast<int8_t>(result));
                case UINT16:
                    if(result > static_cast<int64_t>(4294967295))
                        return Variable(static_cast<uint64_t>(result));
                    if(result < -static_cast<int64_t>(2147483648))
                        return Variable(static_cast<int64_t>(result));
                    if(result > 65535)
                        return Variable(static_cast<uint32_t>(result));
                    if(result < -32768)
                        return Variable(static_cast<int32_t>(result));
                    if(result < 0)
                        return Variable(static_cast<int16_t>(result));
                    return Variable(static_cast<uint16_t>(result));
                case INT16:
                    if(result > static_cast<int64_t>(2147483648) || result < -static_cast<int64_t>(2147483648))
                        return Variable(result);
                    if(result > 32767 || result < -32768)
                        return Variable(static_cast<int32_t>(result));
                    return Variable(static_cast<int16_t>(result));
                case UINT32:
                    if(result > static_cast<int64_t>(4294967295))
                        return Variable(static_cast<uint64_t>(result));
                    if(result < -static_cast<int64_t>(2147483648))
                        return Variable(static_cast<int64_t>(result));
                    if(result < 0)
                        return Variable(static_cast<int32_t>(result));
                    return Variable(static_cast<uint32_t>(result));
                case INT32:
                    if(result > static_cast<int64_t>(2147483648) || result < -static_cast<int64_t>(2147483648))
                        return Variable(result);
                    return Variable(static_cast<int32_t>(result));
                case UINT64:
                    if(result < 0)
                        return Variable(static_cast<int64_t>(result));
                    return Variable(static_cast<uint64_t>(result));
                case INT64:
                    return Variable(result);
                default:
                    return 0;//its bad if this happens
            }
        }

        Variable operator+(Variable a)
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return Variable(To<bool>() || a.To<bool>());
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return Variable(To<double>() + a.To<double>());
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return Variable(To<float>() + a.To<float>());
            }
            uint64_t preResult = To<uint64_t>() + a.To<uint64_t>();
            if(preResult > 9223372036854775807)
                return Variable(static_cast<uint64_t>(preResult));
            int64_t result = To<int64_t>() + a.To<int64_t>();
            return Int64ToVariable(result, Type);
        }
        Variable operator-(Variable a)
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return Variable(To<bool>() || !a.To<bool>());
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return Variable(To<double>() - a.To<double>());
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return Variable(To<float>() - a.To<float>());
            }
            if(To<uint64_t>() > a.To<uint64_t>())
            {
                uint64_t preResult = To<uint64_t>() - a.To<uint64_t>();
                if(preResult > 9223372036854775807)
                    return Variable(static_cast<uint64_t>(preResult));
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
                    return Variable(To<bool>() && a.To<bool>());
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return Variable(To<double>() * a.To<double>());
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return Variable(To<float>() * a.To<float>());
            }
            uint64_t preResult = To<uint64_t>() * a.To<uint64_t>();
            if(preResult > 9223372036854775807)
                return Variable(static_cast<uint64_t>(preResult));
            int64_t result = To<int64_t>() * a.To<int64_t>();
            return Int64ToVariable(result, Type);
        }
        Variable operator/(Variable a)
        {
            if(Type == BOOLEAN || a.Type == BOOLEAN)
            {
                if(Type == BOOLEAN && a.Type == BOOLEAN)
                {
                    return Variable(To<bool>() && !a.To<bool>());
                }
            }
            if(Type == DOUBLE || a.Type == DOUBLE)
            {
                return Variable(To<double>() / a.To<double>());
            }
            if(Type == FLOAT || a.Type == FLOAT)
            {
                return Variable(To<float>() / a.To<float>());
            }
            if(a.To<uint64_t>() != 0)
            {
                uint64_t preResult = To<uint64_t>() / a.To<uint64_t>();
                if(preResult > 9223372036854775807)
                    return Variable(static_cast<uint64_t>(preResult));
            }
            if(a.To<int64_t>() == 0)
                return Variable(false);
            int64_t result = To<int64_t>() / a.To<int64_t>();
            return Int64ToVariable(result, Type);
        }
        Variable operator&(Variable a)
        {
            Variable ret = *this;
            ret.Value &= a.Value;
            return ret;
        }
        Variable operator|(Variable a)
        {
            Variable ret = *this;
            ret.Value |= a.Value;
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