# Dynamic Formulas
This is the Dynamic Formulas source code.

A powerful API for storing, parsing and operating formula expressions with custom variable(Keywords) dynamically.

The parsing of the formula can be done at compile time, meaning that the construction of the optimized formula can be done from a simple string of text before runtime and stored directly into the function binary for fast reading.

The goal of the library is to allows easy and safe declaration of expressions and advanced mathematical manipulation.

## Beta Stage !
This library is already functional at storing and retrieving its result, however, the true value of the tool will be unlocked after the operations that allows formula merging, simplification, chaining and more.

## Code Style
This API was developed to work as an Unreal Engine 5 module, and uses Unreal's default coding style.
However, we plan to separate the Unreal's module to another branch on this repository as an option, and maintain the main branch as the standalone usage, following the STL conventions.

## How to use
### Creating Formulas
Use the FORMULA() macro with a string literal as parameter.
The string must contain the Formula's expression.
 Example:
```
#include "Formula/FormulaBuilder.h"
constexpr auto Formula = FORMULA("SquareRoot(Square(SideA) + Square(SideB)");
```

### Parsing Formulas
Use the GetSolution() method of the TFormula[] class(created by the FORMULA() macro).
Pass the object and the object's method that will be used to parse the keywords of the formula.
```

public:
    double ParseKeyword(const FKeyword& Keyword) const
    {
        if (Keyword == "Strength")
            return Strength;

        else if (Keyword == "Agility")
            return Agility;

        else if (Keyword == "Intelligence")
            return Intelligence;

        return 0.0;
    }

    template<size_t FormulaSize>
    double Operate(const TFormula<FormulaSize>& Formula) const
    {
        return Formula.GetSolution(this, &FSkill::ParseKeyword);
    }
```

### Defining Custom Operations
Open "Operation.h" file.
Include in FOperations class:
  -Declare your custom operation static function. [Line 133]
  -Define your custom operation static object. [Line 207]
  -List your object on the StaticArray. [Line 255]
