#pragma once

#include "Operand.h"
#include "Operation.h"

class FOperandBuffer
{
public:
    FOperandBuffer() = default;

    FOperand Pull()
    {
		if (IsEmpty())
            return FOperand();

        Index--;
        return Buffer[Index];
    }

    void Push(const FOperand& Operand)
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
    FOperand Buffer[FOperations::GetMaxNumberOfOperands()] = {};
    uint8 Index = 0;
};