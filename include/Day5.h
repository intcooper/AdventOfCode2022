#pragma once

#include "DailyTask.h"

#include <deque>
#include <string>
#include <vector>

namespace AdventOfCode
{

class Day5 : public DailyTask
{
  public:
    Day5(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 5 - Supply Stacks";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    std::vector<std::deque<char>> m_stacks;

    void LoadHeader();
    virtual std::string GetResult() const override;
};
}
