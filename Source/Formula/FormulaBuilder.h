#pragma once

#include <bit>
#include "Formula.h"

#define FORMULA_MAX_SCOPES 8

#pragma pack(push, 1) // Toggle off byte alignment on classes.
template<typename T0, typename T1>
struct FTwoDatas
{
    constexpr FTwoDatas(const T0& Data0, const T1& Data1)
        : Data0(Data0), Data1(Data1)
    {}
    T0 Data0;
    T1 Data1;
};
#pragma pack(pop) // Toggle on byte alignment on classes.
class FFormula
{
private:
    using EParticleType = EFormulaParticleType;

    template<size_t ASize, size_t BSize>
    static constexpr bool IsSameString(const char(&StringA)[ASize], const char(&StringB)[BSize], size_t ComparisonLength)
    {
        size_t MinLengthA = ComparisonLength < ASize ? ComparisonLength : ASize;
        size_t MinLengthB = ComparisonLength < BSize ? ComparisonLength : BSize;

        if (MinLengthA != MinLengthB)
            return false;

        bool IsMatching = true;

        for (size_t i = 0; i < MinLengthA && IsMatching; i++)
        {
            IsMatching = (StringA[i] == StringB[i]);
        }

        return IsMatching;
    }

    struct FParsingContext
    {
        enum class EError : uint8
        {
            None = 0,
            NoScopeStartAfterFunctionIdentifier,
            MoreThanOneDecimalPoint,
            ParsingNumberWithoutNumerals,
            ScopeOverload,
            NoScopeToClose,
            ClosingUnfinishedScope,
            CommaOutOfContext,
            NoOperandsNext,
            UnexpectedEnd,
            UnexpectedIdentifier,
            UnexpectedOperandIdentifier,
            NoMatchingSignOperation,
            EndingWithOpenScope,
            OperandLeftUndeclared,
            DataBufferOverload,
        };
        enum class EStage : uint8
        {
            BeforeOperand = 1, // Asking for Number, Variable, PrefixOperation or Function.
            AfterOperand, // Asking for InfixOperation or End.
            FunctionStart, // Asking for (.
            FunctionNext, // Asking for ,.
            FunctionEnd, // Asking for ).
        };
        struct FScope
        {
            constexpr FScope() = default;

            bool IsFunction = false;
            uint8 OperandsLeft = 1;
            uint16 StartIndex = 0;
            uint16 LastPriorityIndex[5] = {};
        };

        constexpr FParsingContext() = default;

        constexpr FScope& ActiveScope() { return Scopes[ScopeIndex]; }
        constexpr void StartScope(uint8 OperandsLeft, bool IsFunction, uint16 StartIndex) 
        { 
			if (ScopeIndex >= FORMULA_MAX_SCOPES - 1)
            {
                Error = EError::ScopeOverload;
                return;
            }

            ScopeIndex++;
            Scopes[ScopeIndex].OperandsLeft = OperandsLeft;
            Scopes[ScopeIndex].IsFunction = IsFunction;
            Scopes[ScopeIndex].StartIndex = StartIndex;
            for (auto& Index : Scopes[ScopeIndex].LastPriorityIndex)
            {
                Index = StartIndex;
            }
        }

        constexpr void CloseScope() 
        { 
            if (ScopeIndex <= 0)
            {
                Error = EError::NoScopeToClose;
                return;
            }
            if (Scopes[ScopeIndex].OperandsLeft != 0)
            {
                Error = EError::ClosingUnfinishedScope;
            }

            ScopeIndex--;
        }

        constexpr void SetPriorityIndex(uint8 Priority, uint16 CurrentIndex) 
        {
            for (int i = Priority-2; i >= 0; i--)
            {
                Scopes[ScopeIndex].LastPriorityIndex[i] = CurrentIndex;
            }
        }

        constexpr uint16 GetPriorityIndexFor(uint8 Priority, uint16 CurrentIndex) 
        { 
            if (Priority == 4)
                return Scopes[ScopeIndex].StartIndex;
            else
                return Scopes[ScopeIndex].LastPriorityIndex[Priority-1];
        }

        EStage Stage = EStage::BeforeOperand;
        EError Error = EError::None;
        FScope Scopes[FORMULA_MAX_SCOPES] = {};
        uint8 ScopeIndex = 0;
    };
    using EParsingStage = FParsingContext::EStage;
    using EParsingError = FParsingContext::EError;



    template<uint16 Size>
    struct DataBuffer
    {
        uint8 Data[Size] = {};
    };

    template<typename T, uint16 DataSize>
    static constexpr void PushIntoData(FParsingContext& OutParsingContext, uint8 (&OutData)[DataSize], uint16& OutIndex, const T& Data)
    {
        using BufferType = DataBuffer<sizeof(Data)>;

        if (sizeof(Data) + OutIndex > DataSize)
        {
            OutParsingContext.Error = EParsingError::DataBufferOverload;
            return;
        }

        BufferType Buffer = std::bit_cast<BufferType>(Data);

        for (size_t i = 0; i < sizeof(Data); i++)
        {
            OutData[OutIndex+i] = Buffer.Data[i];

        }
        OutIndex += sizeof(Data);
    }

    template<typename T, uint16 DataSize>
    static constexpr void PushIntoIndex(FParsingContext& OutParsingContext, uint8 (&OutData)[DataSize], uint16& OutIndex, uint16 Index, const T& Data)
    {
        using BufferType = DataBuffer<sizeof(Data)>;

        if (sizeof(Data) + OutIndex > DataSize)
        {
            OutParsingContext.Error = EParsingError::DataBufferOverload;
            return;
        }

        BufferType Buffer = std::bit_cast<BufferType>(Data);

        for (size_t i = OutIndex + sizeof(Data) - 1; i > Index + sizeof(Data) - 1; i--)
        {
            OutData[i] = OutData[i-sizeof(Data)];
        }

        OutIndex += sizeof(Data);

        for (size_t i = 0; i < sizeof(Data); i++)
        {
            OutData[Index + i] = Buffer.Data[i];
        }
    }

    template<typename T, uint16 DataSize>
    static constexpr void PushIntoDataPriority(FParsingContext& OutParsingContext, uint8 (&OutData)[DataSize], uint16& OutDataIndex, const T& Data, uint8 Priority)
    {
        uint16 PriorityIndex = OutParsingContext.GetPriorityIndexFor(Priority, OutDataIndex);
        PushIntoIndex(OutParsingContext, OutData, OutDataIndex, PriorityIndex, Data);
        for (auto& Index : OutParsingContext.ActiveScope().LastPriorityIndex)
        {
            if (PriorityIndex < Index)
            {
                Index += sizeof(Data);
            }
        }
    }

    template<typename T, uint16 DataSize>
    static constexpr void PushIntoData(FParsingContext& OutParsingContext, char (&OutData)[DataSize], uint16& OutIndex, const T& Data)
    {
        using BufferType = DataBuffer<sizeof(Data)>;

        if (sizeof(Data) + OutIndex > DataSize)
        {
            OutParsingContext.Error = EParsingError::DataBufferOverload;
            return;
        }

        BufferType Buffer = std::bit_cast<BufferType>(Data);

        for (size_t i = 0; i < sizeof(Data); i++)
        {
            OutData[OutIndex+i] = Buffer.Data[i];

        }
        OutIndex += sizeof(Data);
    }

    template<uint16 StringSize, uint16 DataSize>
    static constexpr void ParseSign(FParsingContext& OutParsingContext, uint8(&OutData)[DataSize], uint16& OutDataIndex, uint16& OutStringIndex, const char(&InString)[StringSize])
    {
        using EOperationType = FOperation::ESyntaxType;

        char SignBuffer[2] = {};
        uint16 SignIndex = 0;
        
        PushIntoData(OutParsingContext, SignBuffer, SignIndex, InString[OutStringIndex]);
        OutStringIndex++;

        while (OutStringIndex < StringSize)
        {
            if (IsSign(InString[OutStringIndex]))
            {
                // Continue sign parsing

                PushIntoData(OutParsingContext, SignBuffer, SignIndex, InString[OutStringIndex]);

                OutStringIndex++;
            }
            else
            {
                // End sign parsing
                
                for (auto& OperationRef : FOperations::StaticArray)
                {
                    auto& Operation = OperationRef.get();
                    
                    for (size_t i = 0; i < Operation.GetKeywordsLength(); i++)
                    {
                        const FOperation::FKeyword& Keyword = Operation.GetKeywords()[i];

                        if (Keyword.Size > 2)
                            continue;

                        if (OutParsingContext.Stage == EParsingStage::BeforeOperand && Keyword.Type == FOperation::ESyntaxType::Infix)
                            continue;

                        if (OutParsingContext.Stage == EParsingStage::AfterOperand && Keyword.Type != EOperationType::Infix)
                            continue;
                    
                        uint8 BiggestLength = Keyword.Size > SignIndex ? Keyword.Size : SignIndex;

                        if (!IsSameString(Keyword.Buffer, SignBuffer, BiggestLength))
                            continue;

                        switch (Keyword.Type)
                        {

                        case EOperationType::Prefix: 
                            PushIntoData(OutParsingContext, OutData, OutDataIndex, EParticleType::Operation);
                            PushIntoData(OutParsingContext, OutData, OutDataIndex, FOperations::GetID(Operation));
                            return;

                        case EOperationType::Function:
                            while (OutStringIndex < StringSize && InString[OutStringIndex] == ' ')
                            {
                                OutStringIndex++;
                            }
                            if (OutStringIndex >= StringSize || InString[OutStringIndex] != '(')
                            {
                                OutParsingContext.Error = EParsingError::NoScopeStartAfterFunctionIdentifier;
                                return;
                            }
                            OutStringIndex++;

                            PushIntoData(OutParsingContext, OutData, OutDataIndex, EParticleType::Operation);
                            PushIntoData(OutParsingContext, OutData, OutDataIndex, FOperations::GetID(Operation));

                            OutParsingContext.StartScope(Operation.GetNumberOfOperands(), true, OutDataIndex);
                            OutParsingContext.Stage = EParsingStage::BeforeOperand;
                            return;

                        case EOperationType::Infix:
                            OutParsingContext.SetPriorityIndex(Operation.GetPriority(), OutDataIndex);
                            PushIntoDataPriority(OutParsingContext, OutData, OutDataIndex, 
                                FTwoDatas(EParticleType::Operation, FOperations::GetID(Operation)), Operation.GetPriority()
                            );

                            OutParsingContext.ActiveScope().OperandsLeft++;
                            OutParsingContext.Stage = EParsingStage::BeforeOperand;
                            return;
                        }
                    }
                }
                
                OutParsingContext.Error = EParsingError::NoMatchingSignOperation;
                return;
            }
        }
    }

    template<uint16 StringSize, uint16 DataSize>
    static constexpr void ParseWord(FParsingContext& OutParsingContext, uint8(&OutData)[DataSize], uint16& OutDataIndex, uint16& OutStringIndex, const char(&InString)[StringSize])
    {
        using EOperationType = FOperation::ESyntaxType;

        char KeywordBuffer[256] = {};
        uint16 KeywordSize = 0;
        
        PushIntoData(OutParsingContext, KeywordBuffer, KeywordSize, InString[OutStringIndex]);
        OutStringIndex++;

        while (OutStringIndex < StringSize)
        {
            if (IsLetter(InString[OutStringIndex]) || IsNumeral(InString[OutStringIndex]) || InString[OutStringIndex] == '_')
            {
                // Continue sign parsing

                PushIntoData(OutParsingContext, KeywordBuffer, KeywordSize, InString[OutStringIndex]);

                OutStringIndex++;
            }
            else
            {
                // End sign parsing
                
                for (auto& OperationRef : FOperations::StaticArray)
                {
                    auto& Operation = OperationRef.get();

                    for (size_t i = 0; i < Operation.GetKeywordsLength(); i++)
                    {
                        const FOperation::FKeyword& Keyword = Operation.GetKeywords()[i];

                        if (!IsLetter(Keyword.Buffer[0]))
                            continue;

                        if (OutParsingContext.Stage == EParsingStage::BeforeOperand && Keyword.Type == EOperationType::Infix)
                            continue;

                        if (OutParsingContext.Stage == EParsingStage::AfterOperand && Keyword.Type != EOperationType::Infix)
                            continue;

                        uint8 BiggestSize = Keyword.Size > KeywordSize ? Keyword.Size : KeywordSize;

                        if (!IsSameString(Keyword.Buffer, KeywordBuffer, BiggestSize))
                            continue;

                        switch (Keyword.Type)
                        {
                        case EOperationType::Prefix: 
                            PushIntoData(OutParsingContext, OutData, OutDataIndex, EParticleType::Operation);
                            PushIntoData(OutParsingContext, OutData, OutDataIndex, FOperations::GetID(Operation));

                            OutParsingContext.Stage = EParsingStage::BeforeOperand;
                            return;

                        case EOperationType::Function:
                            while (OutStringIndex < StringSize && InString[OutStringIndex] == ' ')
                            {
                                OutStringIndex++;
                            }
                            if (OutStringIndex >= StringSize || InString[OutStringIndex] != '(')
                            {
                                OutParsingContext.Error = EParsingError::NoScopeStartAfterFunctionIdentifier;
                                return;
                            }
                            OutStringIndex++;

                            OutParsingContext.StartScope(Operation.GetNumberOfOperands(), true, OutDataIndex);

                            PushIntoData(OutParsingContext, OutData, OutDataIndex, EParticleType::Operation);
                            PushIntoData(OutParsingContext, OutData, OutDataIndex, FOperations::GetID(Operation));

                            OutParsingContext.Stage = EParsingStage::BeforeOperand;
                            return;
                            
                        case EOperationType::Infix:
                            OutParsingContext.SetPriorityIndex(Operation.GetPriority(), OutDataIndex);
                            PushIntoDataPriority(OutParsingContext, OutData, OutDataIndex, 
                                FTwoDatas(EParticleType::Operation, FOperations::GetID(Operation)), Operation.GetPriority()
                            );

                            OutParsingContext.ActiveScope().OperandsLeft++;
                            OutParsingContext.Stage = EParsingStage::BeforeOperand;
                            return;
                        }
                    }
                }
                
                // Custom variable parsing

                PushIntoData(OutParsingContext, OutData, OutDataIndex, EParticleType::Keyword);
                PushIntoData(OutParsingContext, OutData, OutDataIndex, (uint8)KeywordSize);

                for (size_t i = 0; i < KeywordSize; i++)
                {
                    PushIntoData(OutParsingContext, OutData, OutDataIndex, KeywordBuffer[i]);
                }

                OutParsingContext.Stage = EParsingStage::AfterOperand;
                OutParsingContext.ActiveScope().OperandsLeft--;

                return;
            }
        }
    }

    template<uint16 StringSize, uint16 DataSize>
    static constexpr void ParseNumber(FParsingContext& OutParsingContext, uint8(&OutData)[DataSize], uint16& OutDataIndex, uint16& OutStringIndex, const char(&InString)[StringSize], bool IsStartingWithDecimal)
    {
        char NumberBuffer[256] = {};
        uint16 NumberIndex = 0;
        
        bool DecimalPointPlaced = IsStartingWithDecimal;

        PushIntoData(OutParsingContext, NumberBuffer, NumberIndex, InString[OutStringIndex]);
        OutStringIndex++;

        while (OutStringIndex < StringSize)
        {
            if (IsNumeral(InString[OutStringIndex]))
            {
                // Continue number parsing
                PushIntoData(OutParsingContext, NumberBuffer, NumberIndex, InString[OutStringIndex]);
            }
            else if (InString[OutStringIndex] == '.')
            {
                if (DecimalPointPlaced == true)
                {
                    OutParsingContext.Error = EParsingError::MoreThanOneDecimalPoint;
                    return;
                }

                // Decimal point placing

                DecimalPointPlaced = true;
                
                PushIntoData(OutParsingContext, NumberBuffer, NumberIndex, '.');
            }
            else
            {
                // End number parsing

                if (NumberIndex == 1 && DecimalPointPlaced == true)
                {
                    OutParsingContext.Error = EParsingError::ParsingNumberWithoutNumerals;
                    return;
                }
                
                double Number = StringTo<double>(NumberBuffer, NumberIndex);
                
                PushIntoData(OutParsingContext, OutData, OutDataIndex, EParticleType::Float64);
                PushIntoData(OutParsingContext, OutData, OutDataIndex, Number);

                OutParsingContext.Stage = EParsingStage::AfterOperand;
                OutParsingContext.ActiveScope().OperandsLeft--;

                return;
            }
            OutStringIndex++;
        }

    }

    template<uint16 StringSize, uint16 DataSize>
    static constexpr void ParseString(FParsingContext& OutParsingContext, uint8 (&OutData)[DataSize], uint16& OutDataIndex, const char(&InString)[StringSize])
    {
        uint16 StringIndex = 0;

        while (StringIndex < StringSize)
        {
            if (OutParsingContext.Error != EParsingError::None)
                return;

            switch (OutParsingContext.Stage)
            {
            case EParsingStage::BeforeOperand:

                // SCOPE

                if (InString[StringIndex] == '(')
                {
                    OutParsingContext.StartScope(1, false, OutDataIndex);
                    StringIndex++;
                }

                // WORDS

                else if (IsLetter(InString[StringIndex]))
                {
                    ParseWord(OutParsingContext, OutData, OutDataIndex, StringIndex, InString);
                }

                // NUMBERS

                else if (IsNumeral(InString[StringIndex]))
                {
                    ParseNumber(OutParsingContext, OutData, OutDataIndex, StringIndex, InString, false);
                }

                else if (InString[StringIndex] == '.')
                {
                    ParseNumber(OutParsingContext, OutData, OutDataIndex, StringIndex, InString, true);
                }

                // SIGNS

                else if (IsSign(InString[StringIndex]))
                {
                    ParseSign(OutParsingContext, OutData, OutDataIndex, StringIndex, InString);
                }

                // OTHER

                else
                {
                    switch (InString[StringIndex])
                    {
                    case ' ':
                        StringIndex++;
                        break;
                    case 0:
                        OutParsingContext.Error = EParsingError::UnexpectedEnd;
                        return;
                    default:
                        OutParsingContext.Error = EParsingError::UnexpectedOperandIdentifier;
                        return;
                    }
                }

                break;



            case EParsingStage::AfterOperand:

                // NEXT OPERAND
                
                if (InString[StringIndex] == ',')
                {
                    if (OutParsingContext.ActiveScope().IsFunction)
                    {
                        if (OutParsingContext.ActiveScope().OperandsLeft <= 0)
                        {
                            OutParsingContext.Error = EParsingError::NoOperandsNext;
                            return;
                        }
                        else
                        {
                            OutParsingContext.Stage = EParsingStage::BeforeOperand;
                            StringIndex++;
                            continue;
                        }
                    }

                    else
                    {
                        OutParsingContext.Error = EParsingError::CommaOutOfContext;
                        return;
                    }
                }

                // END SCOPE

                else if (InString[StringIndex] == ')')
                {
                    OutParsingContext.CloseScope();
                    OutParsingContext.Stage = EParsingStage::AfterOperand;
                    OutParsingContext.ActiveScope().OperandsLeft--;

                    StringIndex++;
                    continue;
                }

                // INFIX SIGN

                else if (IsSign(InString[StringIndex]))
                {
                    ParseSign(OutParsingContext, OutData, OutDataIndex, StringIndex, InString);
                    continue;
                }

                // OTHER

                else
                {
                    switch (InString[StringIndex])
                    {
                    case ' ':
                        StringIndex++;
                        break;

                    case 0:
                        if (OutParsingContext.ScopeIndex != 0)
                            OutParsingContext.Error = EParsingError::EndingWithOpenScope;

                        else if (OutParsingContext.ActiveScope().OperandsLeft != 0)
                            OutParsingContext.Error = EParsingError::OperandLeftUndeclared;

                        return;

                    default:
                        OutParsingContext.Error = EParsingError::UnexpectedIdentifier;
                        return;
                    }
                }

                break;
            }
        }
    }

    template<uint16 DataSize>
    static constexpr void InfixToPrefix(uint8 (&OutData)[DataSize], uint16& OutDataIndex)
    {
        uint8 NewDataBuffer[1000] = {};
        uint16 NewDataIndex = 0;
        
    }

public:
    template<uint16 StringSize>
    static constexpr uint16 GetDataSizeFromString(const char(&String)[StringSize])
    {
        uint16 DataIndex = 0;
        uint8 DataBuffer[1000] = {};
        FParsingContext ParsingContext;

        ParseString(ParsingContext, DataBuffer, DataIndex, String);

        if (ParsingContext.Error != EParsingError::None)
        {
            return 0;
        }

        return DataIndex;
    }

    template<uint16 FormulaSize, uint16 StringSize>
    static constexpr auto Create(const char(&String)[StringSize])
    {
        //static_assert(FormulaSize > 0, "Formula creation need to have size greater than 0.");

        uint16 DataIndex = 0;
        uint8 DataBuffer[1000] = {};
        FParsingContext ParsingContext;
        
        ParseString(ParsingContext, DataBuffer, DataIndex, String);
        
        if constexpr (FormulaSize == 0)
        {
            return ParsingContext.Error;
        }
        else
        {
            return TFormula<FormulaSize>(DataBuffer);
        }
    }

};

#define FORMULA(TEXT) FFormula::Create<FFormula::GetDataSizeFromString( TEXT )>( TEXT )
