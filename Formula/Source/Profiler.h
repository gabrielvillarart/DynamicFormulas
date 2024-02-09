#pragma once

#include <chrono>
#include <string>
#include <iostream>


struct ScopedProfiler
{
    using clock_type = std::chrono::steady_clock;

    ScopedProfiler(const std::string& Name)
        : Name(Name)
    {
        Start = clock_type::now();

        Scope++;
    }

    ~ScopedProfiler()
    {
        Step();

        Scope--;
    }
    
    void Step(const std::string& StepName = "")
    {
        auto Now = clock_type::now();

        auto TimeGap = Now - Start;

        auto TimeGapNumber = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(TimeGap);

        std::string Spaces;
        for (size_t i = 1; i < Scope; i++)
        {
            Spaces += "  ";
        }

        if (StepName == "")
            std::cout << Spaces << "[" << Name << "] " << TimeGapNumber << std::endl;
        else
            std::cout << Spaces << "[" << Name << "(" << StepName << ")] " << TimeGapNumber << std::endl;

        Start = clock_type::now();
    }

private:
    static inline int Scope = 0;
    clock_type::time_point Start;
    const std::string Name;

};

#define PROFILE(NAME) ScopedProfiler ProfilerObj ## ( NAME )
#define PROFILE_STEP(STEP_NAME) ProfilerObj.Step( STEP_NAME )
