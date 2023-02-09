#pragma once

#include "DailyTask.h"
#include "Grid.h"
#include "Point.hpp"

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
    Grid<char> m_map;
    Point m_minPoint{500, 0};
    Point m_maxPoint{0, 0};
    Point m_sandUnit{500, 0};

    void PlotSegment(const Point& start, const Point& end);
    void PrintMap(const Point& source);
    void ParseInputFile();
    int DropSand(Point source);
};
}
