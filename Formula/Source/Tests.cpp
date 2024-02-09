
#include "Formula.h"
#include "Operand.h"
#include "Operation.h"
#include "FormulaBuilder.h"
#include "Profiler.h"

class FSkill
{
public:
    FOperand ParseKeyword(const FKeyword& Keyword) const
    {
        if (Keyword == "Strength")
            return FOperand(Strength);

        else if (Keyword == "Agility")
            return FOperand(Agility);

        else if (Keyword == "Intelligence")
            return FOperand(Intelligence);

        return FOperand(0);
    }

    template<size_t FormulaSize>
    float Operate(const TFormula<FormulaSize>& Formula)
    {
        return Formula.GetSolution(this, &FSkill::ParseKeyword).Get<double>();
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

constexpr auto Formula2 = FORMULA("(5 / Strength * Strength / Strength * Strength) * 0.005");

int main()
{
    FSkill Skill;

    double Result2 = 0.0;

    //while (std::cin.get())
    for(int i = 0; i < 10; i++)
    {
        PROFILE("Main");

        Result2 += Skill.Operate(Formula2);
    }
}
