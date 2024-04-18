
#include "Formula/Formula.h"
#include "Formula/FormulaBuilder.h"
#include "Profiler.h"

class FSkill
{
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

public:
    double Strength = 100.0;
    double Agility = 75.0;
    double Intelligence = 50.0;

};

int main()
{
    FSkill Skill;

    auto Formula = FORMULA("(5 / Strength * Strength / Strength * Strength) * 0.005");

    double Result = Skill.Operate(Formula);
}



