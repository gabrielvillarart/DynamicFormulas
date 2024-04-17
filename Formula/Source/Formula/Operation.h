#pragma once

#include "FormulaCore.h"

class FOperandBuffer;

class FOperation
{
public:
    enum class ESyntaxType : uint8
    {
        None = 0,
        Infix,
        Prefix,
        Function,
    };

public:
    using OperationFunctionType = double(*)(FOperandBuffer&);

    friend class FOperations;

    struct FKeyword
    {
        constexpr FKeyword() = default;

        template<size_t KeywordSize>
        constexpr FKeyword(ESyntaxType Type, const char (&Keyword)[KeywordSize])
            : Type(Type), Size(KeywordSize-1)
        {
            for (size_t i = 0; i < KeywordSize; i++)
            {
                Buffer[i] = Keyword[i];
            }
        }

        const ESyntaxType Type = ESyntaxType::None;
        char Buffer[20] = {};
        uint8 Size = 0;
    };

    constexpr FOperation() = delete;
    constexpr FOperation(const FOperation&) = delete;

    constexpr FOperation(OperationFunctionType Function, uint8 NumberOfOperands, uint8 Priority = 0)
        : Function(Function), NumberOfOperands(NumberOfOperands), Priority(Priority),
        Keywords{}, KeywordsLength(0)
    {}

    constexpr FOperation(OperationFunctionType Function, uint8 NumberOfOperands, FKeyword Keyword, uint8 Priority = 0)
        : Function(Function), NumberOfOperands(NumberOfOperands), Priority(Priority),
        Keywords{Keyword}, KeywordsLength(1)
    {}

    constexpr FOperation(OperationFunctionType Function, uint8 NumberOfOperands, FKeyword Keyword1, FKeyword Keyword2, uint8 Priority = 0)
        : Function(Function), NumberOfOperands(NumberOfOperands), Priority(Priority), 
        Keywords{Keyword1, Keyword2}, KeywordsLength(2)
    {}

public:
    constexpr bool operator == (const FOperation& Other) const
    {
        return Function == Other.Function;
    }
    double operator ()(FOperandBuffer& Operands) const;
    
    const uint8 NumberOfOperands;
    const uint8 Priority;
    const FKeyword Keywords[2];
    const uint8 KeywordsLength;

private:
    const OperationFunctionType Function;
};

class FOperations
{
private:
    using ESyntaxType = FOperation::ESyntaxType;

private:
    static double NoneFunction(FOperandBuffer& OutOperands);
    static double LessThanFunction(FOperandBuffer& OutOperands);
    static double GreaterThanFunction(FOperandBuffer& OutOperands);
    static double LessEqualThanFunction(FOperandBuffer& OutOperands);
    static double GreaterEqualThanFunction(FOperandBuffer& OutOperands);
    static double EqualToFunction(FOperandBuffer& OutOperands);
    static double NotEqualToFunction(FOperandBuffer& OutOperands);
    static double MaximumFunction(FOperandBuffer& OutOperands);
    static double MinimumFunction(FOperandBuffer& OutOperands);
    static double AverageFunction(FOperandBuffer& OutOperands);
    static double SignFunction(FOperandBuffer& OutOperands);
    static double NegationFunction(FOperandBuffer& OutOperands);
    static double AbsoluteFunction(FOperandBuffer& OutOperands);
    static double GetNegativeFunction(FOperandBuffer& OutOperands);
    static double RoundFunction(FOperandBuffer& OutOperands);
    static double RoofFunction(FOperandBuffer& OutOperands);
    static double FloorFunction(FOperandBuffer& OutOperands);
    static double TruncateFunction(FOperandBuffer& OutOperands);
    static double AdditionFunction(FOperandBuffer& OutOperands);
    static double SubtractionFunction(FOperandBuffer& OutOperands);
    static double MultiplicationFunction(FOperandBuffer& OutOperands);
    static double DivisionFunction(FOperandBuffer& OutOperands);
    static double ModuloFunction(FOperandBuffer& OutOperands);
    static double RemainderFunction(FOperandBuffer& OutOperands);
    static double ExponentiationFunction(FOperandBuffer& OutOperands);
    static double SquareFunction(FOperandBuffer& OutOperands);
    static double SquareRootFunction(FOperandBuffer& OutOperands);
    static double CubicRootFunction(FOperandBuffer& OutOperands);
    static double SineFunction(FOperandBuffer& OutOperands);
    static double CosineFunction(FOperandBuffer& OutOperands);
    static double TangentFunction(FOperandBuffer& OutOperands);
    static double SecantFunction(FOperandBuffer& OutOperands);
    static double CosecantFunction(FOperandBuffer& OutOperands);
    static double CotangentFunction(FOperandBuffer& OutOperands);
    static double ArcsineFunction(FOperandBuffer& OutOperands);
    static double ArccosineFunction(FOperandBuffer& OutOperands);
    static double ArctangentFunction(FOperandBuffer& OutOperands);
    static double ArcsecantFunction(FOperandBuffer& OutOperands);
    static double ArccosecantFunction(FOperandBuffer& OutOperands);
    static double ArccotangentFunction(FOperandBuffer& OutOperands);
    static double LinearInterpolationFunction(FOperandBuffer& OutOperands);
    static double MapRangeFunction(FOperandBuffer& OutOperands);


public:
    static constexpr FOperation None = {&NoneFunction, 0};


    // Comparison Operations

    static constexpr FOperation LessThan = {&LessThanFunction, 2, {ESyntaxType::Infix, "<"}, 4};
    static constexpr FOperation GreaterThan = {&GreaterThanFunction, 2, {ESyntaxType::Infix, ">"}, 4};
    static constexpr FOperation LessEqualThan = {&LessEqualThanFunction, 2, {ESyntaxType::Infix, "<="}, 4};
    static constexpr FOperation GreaterEqualThan = {&GreaterEqualThanFunction, 2, {ESyntaxType::Infix, ">="}, 4};
    static constexpr FOperation EqualTo = {&EqualToFunction, 2, {ESyntaxType::Infix, "=="}, 4};
    static constexpr FOperation NotEqualTo = {&NotEqualToFunction, 2, {ESyntaxType::Infix, "!="}, 4};
    static constexpr FOperation Maximum = {&MaximumFunction, 2, {ESyntaxType::Function, "Min"}};
    static constexpr FOperation Minimum = {&MinimumFunction, 2, {ESyntaxType::Function, "Max"}};
    static constexpr FOperation Average = {&AverageFunction, 2, {ESyntaxType::Function, "Average"}};
        

    // Sign Operations
        
    static constexpr FOperation Sign = {&SignFunction, 1, {ESyntaxType::Function, "GetSign"}};
    static constexpr FOperation Negation = {&NegationFunction, 1, {ESyntaxType::Prefix, "-"}};
    static constexpr FOperation Absolute = {&AbsoluteFunction, 1, {ESyntaxType::Function, "Abs"}};
    static constexpr FOperation GetNegative = {&GetNegativeFunction, 1, {ESyntaxType::Function, "GetNegative"}};


    // Real to Integer Operations

    static constexpr FOperation Round = {&RoundFunction, 1, {ESyntaxType::Function, "Round"}};
    static constexpr FOperation Roof = {&RoofFunction, 1, {ESyntaxType::Function, "Roof"}};
    static constexpr FOperation Floor = {&FloorFunction, 1, {ESyntaxType::Function, "Floor"}};
    static constexpr FOperation Truncate = {&TruncateFunction, 1, {ESyntaxType::Function, "Truncate"}};
        

    // Arithmetical Operations

    static constexpr FOperation Addition = {&AdditionFunction, 2, {ESyntaxType::Infix, "+"}, 3};
    static constexpr FOperation Subtraction = {&SubtractionFunction, 2, {ESyntaxType::Infix, "-"}, 3};
    static constexpr FOperation Multiplication = {&MultiplicationFunction, 2, {ESyntaxType::Infix, "*"}, 2};
    static constexpr FOperation Division = {&DivisionFunction, 2, {ESyntaxType::Infix, "/"}, 2};
    static constexpr FOperation Modulo = {&ModuloFunction, 2, {ESyntaxType::Infix, "%"}, 2};
    static constexpr FOperation Remainder = {&RemainderFunction, 2, {ESyntaxType::Function, "Remainder"}};

    static constexpr FOperation Exponentiation = {&ExponentiationFunction, 2, {ESyntaxType::Function, "Power"}, {ESyntaxType::Infix, "^"}, 1};
    static constexpr FOperation Square = {&SquareFunction, 1, {ESyntaxType::Function, "Square"}};
    static constexpr FOperation SquareRoot = {&SquareRootFunction, 1, {ESyntaxType::Function, "SquareRoot"}};
    static constexpr FOperation CubicRoot = {&CubicRootFunction, 1, {ESyntaxType::Function, "CubicRoot"}};
        

    // Geometrical Operations

    static constexpr FOperation Sine = {&SineFunction, 1, {ESyntaxType::Function, "Sine"}};
    static constexpr FOperation Cosine = {&CosineFunction, 1, {ESyntaxType::Function, "Cosine"}};;
    static constexpr FOperation Tangent = {&TangentFunction, 1, {ESyntaxType::Function, "Tangent"}};;
    static constexpr FOperation Secant = {&SecantFunction, 1};
    static constexpr FOperation Cosecant = {&CosecantFunction, 1};
    static constexpr FOperation Cotangent = {&CotangentFunction, 1};
    static constexpr FOperation Arcsine = {&ArcsineFunction, 1};
    static constexpr FOperation Arccosine = {&ArccosineFunction, 1};
    static constexpr FOperation Arctangent = {&ArctangentFunction, 1};
    static constexpr FOperation Arcsecant = {&ArcsecantFunction, 1};
    static constexpr FOperation Arccosecant = {&ArccosecantFunction, 1};
    static constexpr FOperation Arccotangent = {&ArccotangentFunction, 1};
        

    // Interpolation Operations

    static constexpr FOperation LinearInterpolation = {&LinearInterpolationFunction, 3};
    static constexpr FOperation MapRange = {&MapRangeFunction, 5};

	static constexpr std::reference_wrapper<const FOperation> Array[] = {
        None,
        LessThan,
        GreaterThan,
        LessEqualThan,
        GreaterEqualThan,
        EqualTo,
        NotEqualTo,
        Maximum,
        Minimum,
        Average,
        Sign,
        Negation,
        Absolute,
        GetNegative,
        Round,
        Roof,
        Floor,
        Truncate,
        Addition,
        Subtraction,
        Multiplication,
        Division,
        Modulo,
        Remainder,
        Exponentiation,
        Square,
        SquareRoot,
        CubicRoot,
        Sine,
        Cosine,
        Tangent,
        Secant,
        Cosecant,
        Cotangent,
        Arcsine,
        Arccosine,
        Arctangent,
        Arcsecant,
        Arccosecant,
        Arccotangent,
        LinearInterpolation,
        MapRange,
    };

    static constexpr uint8 GetID(const FOperation& Operation)
    {
        for (uint8 i = 0; i < sizeof(Array) / sizeof(std::reference_wrapper<const FOperation>); i++)
        {
            if (Array[i].get() == Operation)
                return i;
        }
        return 0;
    }

    static constexpr uint8 GetMaxNumberOfOperands()
    {
        uint8 Max = 0;
        
        for (uint8 i = 1; i < sizeof(Array) / sizeof(std::reference_wrapper<const FOperation>); i++)
        {
            if (Array[i].get().NumberOfOperands > Max)
                Max = Array[i].get().NumberOfOperands;
        }

        return Max;
    }
};

