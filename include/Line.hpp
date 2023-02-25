#pragma once

#include "Point.hpp"

namespace AdventOfCode
{
/**
 * @brief Abstracts a line in the eucledian plane in the form slope-point.
 */
class Line
{
  public:
    /**
     * @brief Construct a Line passing by the two specified points.
     *
     * @param p1 First point.
     * @param p2 Second point.
     */
    Line(Point p1, Point p2) noexcept
    {
        m_slope =
            static_cast<double>(p1.y - p2.y) / static_cast<double>(p1.x - p2.x);
        // y − y1 = m(x − x1)
        // y = mx - mx1 + y1
        m_point = p1;
    }

    /**
     * @brief Finds the coordinates of the intersection between this line and
     * the specified one.
     *
     * @param other The line to intersect with.
     * @return constexpr Point
     */
    inline constexpr Point Intersect(const Line& other) const
    {
        // line a : y = (ma * x) - (ma * x1a) + y1a
        // line b : y = (mb * x) - (mb * x1b) + y1b
        // solve by x:
        // (ma * x) - (ma * x1a) + y1a = (mb * x) - (mb * x1b) + y1b
        // (ma * x) - (mb * x) = y1b - (mb * x1b) + (ma * x1a) - y1a
        // (ma - mb) * x = y1b - (mb * x1b) + (ma * x1a) - y1a
        // x = (y1b - (mb * x1b) + (ma * x1a) - y1a) / (ma - mb)
        const auto ma = m_slope;
        const auto mb = other.m_slope;
        const auto x1a = m_point.x;
        const auto x1b = other.m_point.x;
        const auto y1a = m_point.y;
        const auto y1b = other.m_point.y;

        const auto xi = (y1b - (mb * x1b) + (ma * x1a) - y1a) / (ma - mb);
        const auto yi = (ma * xi) - (ma * x1a) + y1a;

        return Point(xi, yi);
    }

  private:
    double m_slope; /**< The line's slope */
    Point m_point; /**< The line's point */
};
}