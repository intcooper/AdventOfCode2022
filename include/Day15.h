#pragma once

#include "DailyTask.h"
#include "Grid.h"
#include "Point.hpp"

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
     * @brief Finds the only point outside of the boundaries of the sensors
     * detection area.
     *
     * The algorithm checks only the points of the line specified as first
     * additional command line parameter (argv[2]).
     * If the point is closer to any sensor than its detected beacon, the point
     * is not valid as it lies within the sensor
     * detection area.
     */
    virtual void Task1() override;

    /**
     * @brief Finds the only point outside of the boundaries of the sensors
     * detection area.
     *
     * The algorithm is based on the idea to work out the edges of the sensors'
     * detection areas,
     * i.e. the perimeter of the polygon defined by the points with distance =
     * beacon distance + 1,
     * and find a point of intersection between at least two of the edges of
     * different slope.
     * The intersections points lying outside of all the sensors' detection
     * areas, are potentially
     * the position of the distress beacon.
     */
    virtual void Task2() override;

  private:
    Point m_minPoint{INT_MAX, INT_MAX};
    Point m_maxPoint{INT_MIN, INT_MIN};
    std::map<Point, Point> m_sensorsAndBeacons;

    void ParseInputFile();
    void PlotSegment(const Point& start, const Point& end);
    void PrintMap(const Point& source);
    int DropSand(Point source);
};
}
