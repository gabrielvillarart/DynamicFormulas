#include <chrono>

#include "Formula.h"
#include "Operand.h"
#include "Operation.h"
#include "FormulaBuilder.h"

static std::chrono::steady_clock::time_point Past;

void Mark()
{
    Past = std::chrono::steady_clock::now();
}

auto Click()
{
    std::chrono::steady_clock::time_point Present = std::chrono::steady_clock::now();

    double TimeGap = std::chrono::duration_cast<std::chrono::duration<double>>(Present - Past).count();

    Past = Present;

    return TimeGap;
}

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
        return Formula.GetSolution(this, &FSkill::ParseKeyword).Get<float>();
    }

    void Tick()
    {
        Strength += 1.f;
        Agility += 1.f;
        Intelligence += 1.f;
    }

public:
    float Strength = 100.f;
    float Agility = 75.f;
    float Intelligence = 50.f;

};

constexpr auto Formula0 = FORMULA("5 * 5 * 0.005");
constexpr auto Formula1 = FORMULA("5 * 5 * 0.005");
constexpr auto Formula2 = FORMULA("5 * 5 * 0.005");

int main()
{
    FSkill Skill;

    Mark();

    double Result0 = 0.0;
    double Result1 = 0.0;
    double Result2 = 0.0;

    for (size_t i = 0; i < 15000; i++)
    {
        Result0 += Skill.Operate(Formula0);
        Result1 += Skill.Operate(Formula1);
        Result2 += Skill.Operate(Formula2);

        Skill.Tick();
    }

    double Time = Click();

    std::cout << Time << std::endl;

    std::cin.get();

    Mark();

    for (size_t i = 0; i < 15000; i++)
    {
        Result0 += (double)Skill.Strength * (double)Skill.Strength * 0.005;
        Result1 += (double)Skill.Agility * (double)Skill.Agility * 0.005;
        Result2 += (double)Skill.Intelligence * (double)Skill.Intelligence * 0.005;

        Skill.Tick();
    }

    Time = Click();

    std::cout << Time << std::endl;

    std::cin.get();

    std::cout << Result0 << Result1 << Result2 << std::endl;

    std::cin.get();
}
