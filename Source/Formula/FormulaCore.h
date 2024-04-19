#pragma once

#include "../Core.h"

template<uint64 StringLength>
using FStringLiteral = char[StringLength];

template<uint64 DataLength>
using FDataLiteral = uint8[DataLength];

template<uint64 DataLength = 0>
constexpr uint64 GetValidLength(const FDataLiteral<DataLength>& Data)
{
    for (size_t i = 0; i < DataLength; i++)
    {
        if (Data[i] == 0)
            return i;
    }
    return DataLength;
}


constexpr bool IsNumeral(const char& Character)
{
    return bool(Character >= '0' && Character <= '9');
}

constexpr bool IsSign(const char& Character)
{
    switch (Character)
    {
    case '=': break;
    case '!': break;
    case '&': break;
    case '|': break;
    case '<': break;
    case '>': break;
    case '~': break;
    case '+': break;
    case '-': break;
    case '*': break;
    case '/': break;
    case '%': break;
    case '^': break;
    default:
        return false;
    }

    return true;
}

constexpr bool IsLetter(char Character)
{
    return bool(Character >= 'A' && (Character & 0b11011111) <= 'Z');
}


constexpr int64 Power(int64 n,int64 m)
{
    if(m==1)
        return n;
    else
        return n*(Power(n,m-1));
}

template<size_t StringLength>
struct F_ImplStringTo
{
    template<typename Type>
    static constexpr Type To(const FStringLiteral<StringLength>& String, size_t Length = StringLength - 1)
    {
        return Type(0);
    }
    
    template<>
    static constexpr double To<double>(const FStringLiteral<StringLength>& String, size_t Length)
    {
        double Result= 0.0f;
        int64 DotPosition = 0;

        for (int n = 0; n < Length; n++) {

            if (String[n] == '.')
                DotPosition = Length - n - 1;
        
            else if (!IsNumeral(String[n]))
                return 0.0; // Error

            else
                Result = Result * 10 + (String[n] - '0');
        
        }

        if (DotPosition == 0)
            return Result;

        Result /= (double)Power(10, DotPosition);
        return Result;
    }
    
    template<>
    static constexpr float To<float>(const FStringLiteral<StringLength>& String, size_t Length)
    {
        return (float)To<double>(String, Length);
    }

};


template<typename Type, size_t StringLength>
constexpr Type StringTo(const FStringLiteral<StringLength>& String)
{
    return F_ImplStringTo<StringLength>::To<Type>(String);
}

template<typename Type, size_t StringLength>
constexpr Type StringTo(const FStringLiteral<StringLength>& String, size_t Length)
{
    return F_ImplStringTo<StringLength>::To<Type>(String, Length);
}