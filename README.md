# Dynamic Formulas
This is the Dynamic Formulas source code.<br />

A powerful API for storing, parsing and operating formula expressions with custom variable(Keywords) dynamically.<br />

The parsing of the formula can be done at compile time, meaning that the construction of the optimized formula can be done from a simple string of text before runtime and stored directly into the function binary for fast reading.<br />

The goal of the library is to allows easy and safe declaration of expressions and advanced mathematical manipulation.<br />

## Beta Stage !
This library is already functional at storing and retrieving its result, however, the true value of the tool will be unlocked after the operations that allows formula merging, simplification, chaining and more.<br />

## Code Style
This API was developed to work as an Unreal Engine 5 module, and uses Unreal's default coding style.<br />
However, we plan to separate the Unreal's module to another branch on this repository as an option, and maintain the main branch as the standalone usage, following the STL conventions.<br />

## How to use
### Creating Formulas
Use the FORMULA() macro with a string literal as parameter.<br />
The string must contain the Formula's expression.<br />
 Example:<br />
```
#include "Formula/FormulaBuilder.h"
constexpr auto Formula = FORMULA("SquareRoot(Square(SideA) + Square(SideB)");
```

### Parsing Formulas
Use the GetSolution() method of the TFormula[] class(created by the FORMULA() macro).<br />
Pass the object and the object's method that will be used to parse the keywords of the formula.<br />
 Example:<br />
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
Open "Operation.h" file.<br />
Include in FOperations class:<br />
  -Declare your custom operation static function. [Line 133]<br />
  -Define your custom operation static object. [Line 207]<br />
  -List your object on the StaticArray. [Line 255]<br />
