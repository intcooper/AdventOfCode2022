#pragma once

#include "DailyTask.h"
#include "Monkey.h"

#include <functional>
#include <string>
#include <vector>

namespace AdventOfCode
{
class Day11 : public DailyTask
{
  public:
    Day11(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 11 - Monkey in the Middle";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    std::vector<Monkey> m_monkeys;

    void ParseInputFile();
    void RunTask(int numOfRounds,
                 std::function<uint64_t(uint64_t)> reduceWorry);
};
}
