#pragma once

#include "Operation.h"

class FOperandBuffer
{
public:
    FOperandBuffer() = default;

    double Pull()
    {
		if (IsEmpty())
            return double();

        Index--;
        return Buffer[Index];
    }

    void Push(double Operand)
    {
		if (IsFull())
            return;

        Buffer[Index] = Operand;
        Index++;
    }

    bool IsEmpty() const
    {
        return Index == 0;
    }

    bool IsFull() const
    {
        return Index == 10;
    }

private:
    double Buffer[FOperations::GetMaxNumberOfOperands()] = {};
    uint8 Index = 0;
};