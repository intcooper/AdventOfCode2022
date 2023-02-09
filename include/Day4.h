#pragma once

#include "DailyTask.h"

namespace AdventOfCode
{
class Day4 : public DailyTask
{
  public:
    Day4(const std::string &inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 4 - Camp Cleanup";
    }

    virtual void Task1() override;
    virtual void Task2() override;
};
}
