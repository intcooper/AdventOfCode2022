#pragma once

#include "DailyTask.h"
#include "utils/Point.hpp"

#include <string>
#include <vector>

namespace AdventOfCode
{
class Day12 : public DailyTask
{
  public:
    Day12(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 12 - Hill Climbing Algorithm";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    std::vector<std::string> m_map;
    Utils::Point m_startPos;
    Utils::Point m_endPos;
    std::vector<Utils::Point> m_candidateStartPos;

    std::vector<Utils::Point> Explore(const Utils::Point& start, const Utils::Point& end);
    void ParseInputFile();
};
}
