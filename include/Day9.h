#pragma once

#include "DailyTask.h"
#include "Rope.hpp"

#include <string>

namespace AdventOfCode
{

class Day9 : public DailyTask
{
  public:
    Day9(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 9 - Rope Bridge";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    void RunTask(Rope rope);
};
}
