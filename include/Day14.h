#pragma once

#include "DailyTask.h"
#include "utils/Grid.hpp"
#include "utils/Point.hpp"

#include <string>

namespace AdventOfCode
{
class Day14 : public DailyTask
{
  public:
    Day14(std::string inputFileName);

    inline virtual std::string GetTitle() const override
    {
        return "Day 14 - Regolith Reservoir";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    Utils::Grid<char> m_map;
    Utils::Point m_minPoint{500, 0};
    Utils::Point m_maxPoint{0, 0};
    Utils::Point m_sandUnit{500, 0};

    void PlotSegment(const Utils::Point& start, const Utils::Point& end);
    void PrintMap(const Utils::Point& source);
    void ParseInputFile();
    int DropSand(Utils::Point source);
};
}
