#pragma once

#include "Core.h"

class FOperand
{
 private:
    enum class EType : uint8
    {
        None = 0,
        UInt8,
        UInt16,
        UInt32,
        UInt64,
        Int8,
        Int16,
        Int32,
        Int64,
        Float32,
        Float64,
    };
 public:

    constexpr FOperand() = default;

    template <typename T>
    constexpr FOperand(T Value)
    {
             if constexpr (std::is_same_v<T, uint8>) { UInt8 = Value; Type = EType::UInt8; }
        else if constexpr (std::is_same_v<T, uint16>) { UInt16 = Value; Type = EType::UInt16; }
        else if constexpr (std::is_same_v<T, uint32>) { UInt32 = Value; Type = EType::UInt32; }
        else if constexpr (std::is_same_v<T, uint64>) { UInt64 = Value; Type = EType::UInt64; }

        else if constexpr (std::is_same_v<T, int8>)  { Int8 = Value; Type = EType::Int8; }
        else if constexpr (std::is_same_v<T, int16>) { Int16 = Value; Type = EType::Int16; }
        else if constexpr (std::is_same_v<T, int32>) { Int32 = Value; Type = EType::Int32; }
        else if constexpr (std::is_same_v<T, int64>) { Int64 = Value; Type = EType::Int64; }

        else if constexpr (std::is_same_v<T, float>) { Float32 = Value; Type = EType::Float32; }
        else if constexpr (std::is_same_v<T, double>) { Float64 = Value; Type = EType::Float64; }

        //else static_assert(false, "Invalid template argument");
    }

    template<typename T>
    constexpr T Get() const 
    { 
        switch (Type)
        {
            case EType::UInt8: return (T)UInt8;
            case EType::UInt16: return (T)UInt16;
            case EType::UInt32: return (T)UInt32;
            case EType::UInt64: return (T)UInt64;

            case EType::Int8: return (T)Int8;
            case EType::Int16: return (T)Int16;
            case EType::Int32: return (T)Int32;
            case EType::Int64: return (T)Int64;

            case EType::Float32: return (T)Float32;
            case EType::Float64: return (T)Float64;
        }
        return (T)0;
    }

    EType Type = EType::None;

private:
    union
    {
        uint8  UInt8;
        uint16 UInt16;
        uint32 UInt32;
        uint64 UInt64 = 0;
        int8  Int8;
        int16 Int16;
        int32 Int32;
        int64 Int64;
        float Float32;
        double Float64;
    };

};
