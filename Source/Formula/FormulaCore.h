#pragma once

#include "../Core.h"

template<std::size_t size = 0>
constexpr std::size_t GetValidLength(const char (&Data)[size])
{
    for (size_t i = 0; i < size; i++)
    {
        if (Data[i] == 0)
            return i;
    }
    return size;
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

constexpr bool IsLetter(const char& Character)
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

template<size_t Size>
struct F_ImplStringTo
{
    template<typename Type>
    static constexpr Type To(const char (&String)[Size], size_t Length = Size - 1)
    {
        return Type(0);
    }
    
    template<>
    static constexpr double To<double>(const char (&String)[Size], size_t Length)
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
    static constexpr float To<float>(const char (&String)[Size], size_t Length)
    {
        return (float)To<double>(String, Length);
    }

};


template<typename Type, size_t Size>
constexpr Type StringTo(const char (&String)[Size])
{
    return F_ImplStringTo<Size>::To<Type>(String);
}

template<typename Type, size_t Size>
constexpr Type StringTo(const char (&String)[Size], size_t Length)
{
    return F_ImplStringTo<Size>::To<Type>(String, Length);
}