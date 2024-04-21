#pragma once

#include "FormulaCore.h"
#include "Operation.h"
#include "OperandBuffer.h"
#include "Keyword.h"

enum class EFormulaParticleType : uint8
{
    None = 0,

    Operation,

    Keyword,

    Float64,
};


template<size_t FormulaLength>
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

    template<size_t DataLength>
    constexpr TFormula(const FDataLiteral<DataLength>& Buffer)
    {
        size_t WorkSize = FormulaLength < DataLength? FormulaLength : DataLength;
        for (size_t i = 0; i < WorkSize; i++)
        {
            Data[i] = (uint8)Buffer[i];
        }
    }

    template<typename T>
    struct FSolutionInfo
    {
        using FunctionSignature = double(T::*)(const FKeyword&) const;

        FSolutionInfo(const T* ObjectPtr, const FunctionSignature ParseFunctionPtr)
			: ObjectPtr(ObjectPtr), FunctionPtr(ParseFunctionPtr)
        {}

        uint16 Index = 0;
		const T* const ObjectPtr;
		const FunctionSignature FunctionPtr;
    };

    template<typename T>
    void ParseOperation(FOperandBuffer& OutOperands, FSolutionInfo<T>& OutInfo) const
    {
        uint8 OperationID = PullFromData<uint8>(OutInfo.Index);
        
        const FOperation& Operation = FOperations::StaticArray[OperationID].get();
        
        FOperandBuffer OperationOperands;
        
        for (size_t i = 0; i < Operation.GetNumberOfOperands(); i++)
        {
            ParseSolution(OperationOperands, OutInfo);
        }
        
        auto Result = Operation(OperationOperands);
        
        OutOperands.Push(Result);
    }

    template<typename T>
    void ParseKeyword(FOperandBuffer& OutOperands, FSolutionInfo<T>& OutInfo) const
    {
        uint8 Length = PullFromData<uint8>(OutInfo.Index);

        FKeyword Keyword = FKeyword((const char*)&Data[OutInfo.Index], Length);

		double Operand = ((*OutInfo.ObjectPtr).*OutInfo.FunctionPtr)(Keyword);

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

        case EFormulaParticleType::Float64:

            OutOperands.Push(double(PullFromData<double>(OutInfo.Index)));

            break;

        }
    }

public:
    template<typename T>
    using ParseKeywordSignature = double(T::*)(const FKeyword&) const;

    template<typename T>
    double GetSolution(const T& ObjectPtr, ParseKeywordSignature<T> ParseKeywordFunction) const
    {
        FSolutionInfo<T> Info(&ObjectPtr, ParseKeywordFunction);
        FOperandBuffer Operands;

        ParseSolution(Operands, Info);

        return Operands.Pull();
    }

    //using ParseKeywordStaticSignature = double()(const FKeyword&) const;

    //template<typename T>
    //double GetSolution(ParseKeywordStaticSignature ParseKeywordFunction) const
    //{
    //    FSolutionInfo<T> Info(nullptr, ParseKeywordFunction);
    //    FOperandBuffer Operands;

    //    ParseSolution(Operands, Info);

    //    return Operands.Pull();
    //}

    constexpr uint8 GetSize() const { return FormulaLength; }

private:
    uint8 Data[FormulaLength] = {};
};
