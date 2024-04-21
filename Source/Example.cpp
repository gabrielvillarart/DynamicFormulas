
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

    template<size_t FormulaLength>
    double Operate(const TFormula<FormulaLength>& Formula) const
    {
        return Formula.GetSolution(*this, &FSkill::ParseKeyword);
    }

public:
    double Strength = 100.0;
    double Agility = 75.0;
    double Intelligence = 50.0;

};



int main()
{
    FSkill Skill;

    double SumOfAttributes = Skill.Operate(FORMULA("Strength + Agility + Intelligence"));
    // Or FORMULA("Strength + Agility + Intelligence").GetSolution(Skill, &FSkill::ParseKeyword);
}


