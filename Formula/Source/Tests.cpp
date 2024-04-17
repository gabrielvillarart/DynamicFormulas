
#include "Formula/Formula.h"
#include "Formula/Operation.h"
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

    void Tick()
    {
        Strength += 1.0;
        Agility += 1.0;
        Intelligence += 1.0;
    }

public:
    double Strength = 100.0;
    double Agility = 75.0;
    double Intelligence = 50.0;

};

int main()
{
    FSkill Skill;

    double Result = 0.0;
    while (true)
    {
        {
            PROFILE("Main");
            for (int i = 0; i < 10000; i++)
            {
                constexpr auto Formula = FORMULA("(5 / Strength * Strength / Strength * Strength) * 0.005");
                Result += Skill.Operate(Formula);
                Skill.Tick();
            }
        }

        std::cin.get();
    }
}
