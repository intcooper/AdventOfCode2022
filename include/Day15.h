#pragma once

#include "DailyTask.h"
#include "utils/Grid.hpp"
#include "utils/Point.hpp"

#include <map>
#include <string>

namespace AdventOfCode
{
class Day15 : public DailyTask
{
  public:
    Day15(std::string inputFileName, std::string params);

    inline virtual std::string GetTitle() const override
    {
        return "Day 15 - Beacon Exclusion Zone";
    }

    /**
     * @brief Finds the number of points inside the boundaries of any sensor
     * detection area for the specified row.
     *
     * The algorithm checks only the points of the row specified as first
     * additional command line parameter (argv[2]).
     * If the point is closer to any sensor than its detected beacon, the point
     * is not valid as it lies within the sensor detection area.
     */
    virtual void Task1() override;

    /**
     * @brief Finds the only point outside of the boundaries of the sensors
     * detection area.
     *
     * The algorithm is based on the idea to work out the edges of the sensors'
     * detection areas, i.e. the perimeter of the polygon defined by the points
     * with distance = beacon distance + 1, and find a point of intersection
     * between at least two of the edges of different slope.
     * The intersections points lying outside of all the sensors' detection
     * areas, are potentially the position of the distress beacon.
     */
    virtual void Task2() override;

  private:
    Utils::Point m_minPoint{std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
    Utils::Point m_maxPoint{std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
    std::map<Utils::Point, Utils::Point> m_sensorsAndBeacons;

    void ParseInputFile();
    void PlotSegment(const Utils::Point& start, const Utils::Point& end);
    void PrintMap(const Utils::Point& source);
    int DropSand(Utils::Point source);
};
}
