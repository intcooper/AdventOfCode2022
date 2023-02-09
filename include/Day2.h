#pragma once

#include "DailyTask.h"

#include <array>

namespace AdventOfCode
{
class Day2 : public DailyTask
{
  public:
    Day2(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 2 - Rock Paper Scissors";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    static constexpr std::array<uint8_t, 3> WinCombinations = {2, 3, 1};
    static constexpr std::array<uint8_t, 3> LossCombinations = {3, 1, 2};
};
}