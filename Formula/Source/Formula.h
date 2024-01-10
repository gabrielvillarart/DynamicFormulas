#pragma once

#include "Core.h"
#include "Operand.h"
#include "Operation.h"
#include "OperandBuffer.h"
#include "Keyword.h"

enum class EFormulaParticleType : uint8
{
    None = 0,

    Operation,

    Keyword,

    Float32,
    Float64,
    UInt8,
    UInt16,
    UInt32,
    UInt64,
    Int8,
    Int16,
    Int32,
    Int64,
};


template<size_t FormulaSize>
class TFormula
{
public:
    friend class FFormula;

private:
    template<typename T>
    const T& PullFromData(uint16& OutIndex) const
    {
        const T& Ref = *(T*)&(Data[OutIndex]);

        OutIndex += sizeof(T);

        return Ref;
    }

    TFormula() = delete;
    TFormula(const TFormula&) = delete;

    template<size_t BufferSize>
    constexpr TFormula(const uint8(&Buffer)[BufferSize])
    {
        size_t WorkSize = FormulaSize < BufferSize? FormulaSize : BufferSize;
        for (size_t i = 0; i < WorkSize; i++)
        {
            Data[i] = (uint8)Buffer[i];
        }
    }

    template<typename T>
    struct FSolutionInfo
    {
        using FunctionType = FOperand(T::*)(const FKeyword&) const;

        FSolutionInfo(const T* ObjectPtr, const FunctionType ParseFunctionPtr)
			: ObjectPtr(ObjectPtr), FunctionPtr(ParseFunctionPtr)
        {}

        uint16 Index = 0;
		const T* const ObjectPtr;
		const FunctionType FunctionPtr;
    };

    template<typename T>
    void ParseOperation(FOperandBuffer& OutOperands, FSolutionInfo<T>& OutInfo) const
    {
        uint8 OperationID = PullFromData<uint8>(OutInfo.Index);

        const FOperation& Operation = FOperations::Array[OperationID].get();
        
        FOperandBuffer OperationOperands;

        for (size_t i = 0; i < Operation.NumberOfOperands; i++)
        {
            ParseSolution(OperationOperands, OutInfo);
        }

        OutOperands.Push(Operation(OperationOperands));
    }

    template<typename T>
    void ParseKeyword(FOperandBuffer& OutOperands, FSolutionInfo<T>& OutInfo) const
    {
        uint8 Length = PullFromData<uint8>(OutInfo.Index);

        FKeyword Keyword = FKeyword((const char*)&Data[OutInfo.Index], Length);

		FOperand Operand = ((*OutInfo.ObjectPtr).*OutInfo.FunctionPtr)(Keyword);

        OutInfo.Index += Length; 

        OutOperands.Push(Operand);
    }
    
    template<typename T>
    void ParseSolution(FOperandBuffer& OutOperands, FSolutionInfo<T>& OutInfo) const
    {
		auto& ParticleType = PullFromData<EFormulaParticleType>(OutInfo.Index);

        switch (ParticleType)
        {
        case EFormulaParticleType::Operation:

            ParseOperation(OutOperands, OutInfo);

            break;

        case EFormulaParticleType::Keyword:

            ParseKeyword(OutOperands, OutInfo);

            break;

        case EFormulaParticleType::Float32:

            OutOperands.Push(FOperand(PullFromData<float>(OutInfo.Index)));

            break;

        case EFormulaParticleType::Float64:

            OutOperands.Push(FOperand(PullFromData<double>(OutInfo.Index)));

            break;

        case EFormulaParticleType::UInt8:

            OutOperands.Push(FOperand(PullFromData<uint8>(OutInfo.Index)));

            break;

        case EFormulaParticleType::UInt16:

            OutOperands.Push(FOperand(PullFromData<uint16>(OutInfo.Index)));

            break;

        case EFormulaParticleType::UInt32:

            OutOperands.Push(FOperand(PullFromData<uint32>(OutInfo.Index)));

            break;

        case EFormulaParticleType::UInt64:

            OutOperands.Push(FOperand(PullFromData<uint64>(OutInfo.Index)));

            break;

        case EFormulaParticleType::Int8:

            OutOperands.Push(FOperand(PullFromData<int8>(OutInfo.Index)));

            break;

        case EFormulaParticleType::Int16:

            OutOperands.Push(FOperand(PullFromData<int16>(OutInfo.Index)));

            break;

        case EFormulaParticleType::Int32:

            OutOperands.Push(FOperand(PullFromData<int32>(OutInfo.Index)));

            break;

        case EFormulaParticleType::Int64:

            OutOperands.Push(FOperand(PullFromData<int64>(OutInfo.Index)));

            break;

        }
    }

public:
    template<typename T>
    FOperand GetSolution(const T* ObjectPtr, FOperand(T::*ParseFunctionPtr)(const FKeyword&) const) const
    {
        FSolutionInfo<T> Info(ObjectPtr, ParseFunctionPtr);
        FOperandBuffer Operands;

        ParseSolution(Operands, Info);

        return Operands.Pull();
    }

private:
    uint8 Data[FormulaSize] = {};
};
