#include <stdint.h>

#define VARIABLE_VALUE_ALIGN (alignof(uint64_t) > alignof(size_t)? alignof(uint64_t) : alignof(size_t))
#define VARIABLE_VALUE_MINSIZE (sizeof(uint64_t) > 2*sizeof(size_t)? sizeof(uint64_t) : 2*sizeof(size_t))
#define VARIABLE_ALIGN (VARIABLE_VALUE_ALIGN > alignof(OperationArchitecture::VariableType)? VARIABLE_VALUE_ALIGN : alignof(OperationArchitecture::VariableType))
#define VARIABLE_SIZE (VARIABLE_VALUE_MINSIZE + (VARIABLE_VALUE_MINSIZE % alignof(OperationArchitecture::VariableType) == 0? 0 : alignof(OperationArchitecture::VariableType) - (VARIABLE_VALUE_MINSIZE % alignof(OperationArchitecture::VariableType))) + sizeof(OperationArchitecture::VariableType))
#define VARIABLE_SIZE_ALIGNED (VARIABLE_SIZE + (VARIABLE_SIZE % VARIABLE_ALIGN == 0? 0 : VARIABLE_ALIGN - (VARIABLE_SIZE % VARIABLE_ALIGN)))
#define VARIABLE_VALUE_SIZE (VARIABLE_SIZE_ALIGNED - sizeof(OperationArchitecture::VariableType) - ((VARIABLE_SIZE_ALIGNED - sizeof(OperationArchitecture::VariableType))) % alignof(OperationArchitecture::VariableType))

#ifndef VARIABLETYPE_H
#define VARIABLETYPE_H
namespace OperationArchitecture
{
    enum VariableType : uint8_t
    {
        VOID = 0,
        UINT8 = 1,
        UINT16 = 2,
        UINT32 = 3,
        UINT64 = 4,
        INT8 = 5,
        INT16 = 6,
        INT32 = 7,
        INT64 = 8,
        FLOAT = 9,
        DOUBLE = 10,
        BOOLEAN = 11,
        POINTER = 12,
        OTHER = 13,
        BIGOTHER = 14
    };
    inline size_t VariableTypeSizeOf(VariableType type)
    {
        switch(type)
        {
            case VariableType::UINT8: return sizeof(uint8_t);
            case VariableType::UINT16: return sizeof(uint16_t);
            case VariableType::UINT32: return sizeof(uint32_t);
            case VariableType::UINT64: return sizeof(uint64_t);
            case VariableType::INT8: return sizeof(int8_t);
            case VariableType::INT16: return sizeof(int16_t);
            case VariableType::INT32: return sizeof(int32_t);
            case VariableType::INT64: return sizeof(int64_t);
            case VariableType::FLOAT: return sizeof(float);
            case VariableType::DOUBLE: return sizeof(double);
            case VariableType::BOOLEAN: return sizeof(bool);
            case VariableType::POINTER: return sizeof(void *);
            case VariableType::OTHER: return VARIABLE_VALUE_SIZE;
            case VariableType::BIGOTHER:
            case VariableType::VOID: 
                return 0;
        }
        return 0;
    }
    inline size_t VariableTypeAlignOf(VariableType type)
    {
        switch(type)
        {
            case VariableType::UINT8: return alignof(uint8_t);
            case VariableType::UINT16: return alignof(uint16_t);
            case VariableType::UINT32: return alignof(uint32_t);
            case VariableType::UINT64: return alignof(uint64_t);
            case VariableType::INT8: return alignof(int8_t);
            case VariableType::INT16: return alignof(int16_t);
            case VariableType::INT32: return alignof(int32_t);
            case VariableType::INT64: return alignof(int64_t);
            case VariableType::FLOAT: return alignof(float);
            case VariableType::DOUBLE: return alignof(double);
            case VariableType::BOOLEAN: return alignof(bool);
            case VariableType::POINTER: return alignof(void *);
            case VariableType::OTHER: return VARIABLE_VALUE_ALIGN;
            case VariableType::BIGOTHER:
            case VariableType::VOID: 
                break;
                //this is bad 
        }
        return 0;
    }
}
#endif