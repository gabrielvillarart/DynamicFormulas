#pragma once

#include "FormulaCore.h"

class FOperandBuffer;

class FOperation
{
private:
    using OperationFunctionType = double(*)(const FOperandBuffer&);

    friend class FOperations;

public:
    enum class ESyntaxType : uint8
    {
        None = 0,
        Infix,
        Prefix,
        Function,
    };

    struct FKeyword
    {
        constexpr FKeyword() = default;

        template<size_t KeywordLength>
        constexpr FKeyword(ESyntaxType Type, const FStringLiteral<KeywordLength>& Keyword)
            : Type(Type), Length(KeywordLength-1)
        {
            for (size_t i = 0; i < KeywordLength; i++)
            {
                Buffer[i] = Keyword[i];
            }
        }

        const ESyntaxType Type = ESyntaxType::None;
        char Buffer[20] = {};
        uint8 Length = 0;
    };

private:
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
    constexpr uint8 GetNumberOfOperands() const { return NumberOfOperands; }
    constexpr uint8 GetPriority() const { return Priority; }
    constexpr const FKeyword* GetKeywords() const { return Keywords; }
    constexpr uint8 GetKeywordsLength() const { return KeywordsLength; }

    constexpr bool operator == (const FOperation& Other) const
    {
        return Function == Other.Function;
    }
    double operator ()(const FOperandBuffer& Operands) const;

private:
    const uint8 NumberOfOperands;
    const uint8 Priority;
    const FKeyword Keywords[2];
    const uint8 KeywordsLength;
    const OperationFunctionType Function;
};

class FOperations
{
private:
    using ESyntaxType = FOperation::ESyntaxType;

private: // Functions
    static double NoneFunction(const FOperandBuffer& OutOperands);
    static double LessThanFunction(const FOperandBuffer& OutOperands);
    static double GreaterThanFunction(const FOperandBuffer& OutOperands);
    static double LessEqualThanFunction(const FOperandBuffer& OutOperands);
    static double GreaterEqualThanFunction(const FOperandBuffer& OutOperands);
    static double EqualToFunction(const FOperandBuffer& OutOperands);
    static double NotEqualToFunction(const FOperandBuffer& OutOperands);
    static double MaximumFunction(const FOperandBuffer& OutOperands);
    static double MinimumFunction(const FOperandBuffer& OutOperands);
    static double AverageFunction(const FOperandBuffer& OutOperands);
    static double SignFunction(const FOperandBuffer& OutOperands);
    static double NegationFunction(const FOperandBuffer& OutOperands);
    static double AbsoluteFunction(const FOperandBuffer& OutOperands);
    static double GetNegativeFunction(const FOperandBuffer& OutOperands);
    static double RoundFunction(const FOperandBuffer& OutOperands);
    static double RoofFunction(const FOperandBuffer& OutOperands);
    static double FloorFunction(const FOperandBuffer& OutOperands);
    static double TruncateFunction(const FOperandBuffer& OutOperands);
    static double AdditionFunction(const FOperandBuffer& OutOperands);
    static double SubtractionFunction(const FOperandBuffer& OutOperands);
    static double MultiplicationFunction(const FOperandBuffer& OutOperands);
    static double DivisionFunction(const FOperandBuffer& OutOperands);
    static double ModuloFunction(const FOperandBuffer& OutOperands);
    static double RemainderFunction(const FOperandBuffer& OutOperands);
    static double ExponentiationFunction(const FOperandBuffer& OutOperands);
    static double SquareFunction(const FOperandBuffer& OutOperands);
    static double SquareRootFunction(const FOperandBuffer& OutOperands);
    static double CubicRootFunction(const FOperandBuffer& OutOperands);
    static double SineFunction(const FOperandBuffer& OutOperands);
    static double CosineFunction(const FOperandBuffer& OutOperands);
    static double TangentFunction(const FOperandBuffer& OutOperands);
    static double SecantFunction(const FOperandBuffer& OutOperands);
    static double CosecantFunction(const FOperandBuffer& OutOperands);
    static double CotangentFunction(const FOperandBuffer& OutOperands);
    static double ArcsineFunction(const FOperandBuffer& OutOperands);
    static double ArccosineFunction(const FOperandBuffer& OutOperands);
    static double ArctangentFunction(const FOperandBuffer& OutOperands);
    static double ArcsecantFunction(const FOperandBuffer& OutOperands);
    static double ArccosecantFunction(const FOperandBuffer& OutOperands);
    static double ArccotangentFunction(const FOperandBuffer& OutOperands);
    static double LinearInterpolationFunction(const FOperandBuffer& OutOperands);
    static double MapRangeFunction(const FOperandBuffer& OutOperands);

    /* Custom Operations:
    *  Declare your custom operation functions below.
    */

public: // Static Objects
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

    
    /* Custom Operations:
    *  Define your custom operation static objects below.
    */

public: // Static Array
	static constexpr std::reference_wrapper<const FOperation> StaticArray[] = {
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
        /* Custom Operations:
        *  List custom operation static objects below.
        */
    };

    static constexpr uint8 GetID(const FOperation& Operation)
    {
        for (uint8 i = 0; i < sizeof(StaticArray) / sizeof(std::reference_wrapper<const FOperation>); i++)
        {
            if (StaticArray[i].get() == Operation)
                return i;
        }
        return 0;
    }

    static constexpr uint8 GetMaxNumberOfOperands()
    {
        uint8 Max = 0;
        
        for (uint8 i = 1; i < sizeof(StaticArray) / sizeof(std::reference_wrapper<const FOperation>); i++)
        {
            if (StaticArray[i].get().NumberOfOperands > Max)
                Max = StaticArray[i].get().NumberOfOperands;
        }

        return Max;
    }
};

