#pragma once

#include "DailyTask.h"

#include <numeric>
#include <vector>

namespace AdventOfCode
{

class Day3 : public DailyTask
{
  public:
    Day3(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 3 - Rucksack Reorganization";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    inline uint32_t GetPriority(std::vector<char> items) const
    {
        const std::string alphabet{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

        return std::accumulate(items.begin(), items.end(), 0, [&alphabet](uint32_t total, char c) -> uint32_t 
        {
            const auto charPos = std::find(alphabet.begin(), alphabet.end(), c);
            return total + static_cast<uint32_t>(std::distance(alphabet.begin(), charPos) + 1);
        });
    }
};
}