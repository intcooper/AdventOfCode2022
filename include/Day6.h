#pragma once

#include "DailyTask.h"

#include <string>

namespace AdventOfCode
{

class Day6 : public DailyTask
{
  public:
    Day6(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 6 - Tuning Trouble";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    size_t GetMarkerStart(uint8_t markerSize);
};
}
