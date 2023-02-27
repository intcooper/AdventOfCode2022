#pragma once

#include <algorithm>
#include <optional>
#include <ostream>

namespace AdventOfCode
{
/**
 * @brief Abtraction of a point in the euclidean plane.
 *
 */
struct Point
{
    int x; /**< abscissa */
    int y; /**< ordinate */

    /**
     * @brief Default constructor.
     */
    constexpr Point() noexcept
        : x{0}
        , y{0}
    {
    }

    /**
     * @brief Destructor.
     * @remark The syntax "= default" makes the build fail with gcc.
     */
    virtual constexpr ~Point(){};

    /**
     * @brief Constructs a point at the specified coordinates.
     * @param x1 abscissa of the point.
     * @param y1 ordinate of the point.
     */
    constexpr Point(int x1, int y1) noexcept
        : x{x1}
        , y{y1}
    {
    }

    /**
     * @brief Copy Constructor.
     * @param other The point to copy from.
     */
    constexpr Point(const Point& other) noexcept
        : x{other.x}
        , y{other.y}
    {
    }

    /**
     * @brief Move Constructor.
     * @param other The point to move from.
     */
    constexpr Point(Point&& other) noexcept
        : x{other.x}
        , y{other.y}
    {
    }

    /**
     * @brief Copy assignment operator.
     *
     * @param other The point to be assigned from.
     * @return Point& A reference to this point instance.
     */
    Point& operator=(const Point& other)
    {
        return *this = Point(other);
    }

    /**
     * @brief Move assignment operator.
     *
     * @param other The point to be assigned from.
     * @return Point& A reference to this point instance.
     */
    Point& operator=(Point&& other) noexcept
    {
        std::swap(x, other.x);
        std::swap(y, other.y);
        return *this;
    }

    /**
     * @brief Equal-to operator
     *
     * @param other The point instance to be compared.
     * @return true If this point is at the same coordinates of the other.
     * @return false If this point is not at the same coordinates of the other.
     */
    constexpr bool operator==(const Point& other) const
    {
        return this->x == other.x && this->y == other.y;
    }

    /**
     * @brief Not-equal-to operator.
     *
     * @param other The point instance to be compared.
     * @return true If this point is not at the same coordinates of the other.
     * @return false If this point is at the same coordinates of the other.
     */
    constexpr bool operator!=(const Point& other) const
    {
        return !operator==(other);
    }

    /**
     * @brief Subtraction operator.
     * It subtracts the coordinates of the specified point (x2, y2) from the
     * coordinates of this point (x1, y1).
     * The result is a new point with coordinates (x1 - x2, y1 - y2).
     * @param other The point instance to be subtracted.
     * @return constexpr Point The point subtraction results.
     */
    constexpr Point operator-(const Point& other) const
    {
        return {this->x - other.x, this->y - other.y};
    }

    /**
     * @brief Subtraction operator.
     * It subtracts the specified integer value (i) from the coordinates of this
     * point (x1, y1).
     * The result is a new point with coordinates (x1 - i, y1 - i).
     * @param i The integer value to be subtracted.
     * @return constexpr Point The subtraction result point.
     */
    constexpr Point operator-(int i) const
    {
        return {this->x - i, this->y - i};
    }

    /**
     * @brief Addition operator.
     * It adds the coordinates of the specified point (x2, y2) to the
     * coordinates of this point (x1, y1).
     * The result is a new point with coordinates (x1 + x2, y1 + y2).
     * @param other The point instance to be added.
     * @return constexpr Point The addition result point.
     */
    constexpr Point operator+(const Point& other) const
    {
        return {this->x + other.x, this->y + other.y};
    }

    /**
     * @brief Multiplication operator.
     * It multiplies the coordinates of this point (x1, y1) by the specified
     * integer value (i). The result is a new point with coordinates
     * (x1 * i, y1 * i).
     * @param i The integer value to be multiplied by.
     * @return constexpr Point The multiplication result point.
     */
    constexpr Point operator*(int i) const
    {
        return {this->x * i, this->y * i};
    }

    /**
     * @brief Addition-assignment operator.
     *
     * @param other
     * @return constexpr Point&
     */
    constexpr Point& operator+=(const Point& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    /**
     * @brief Division-assignment operator.
     *
     * @param other
     * @return constexpr Point&
     */
    Point& operator/=(const Point& other)
    {
        this->x /= std::abs(other.x == 0 ? 1 : other.x);
        this->y /= std::abs(other.y == 0 ? 1 : other.y);

        return *this;
    }

    /**
     * @brief Less-than operator.
     *
     * @param other The point to be compared to.
     * @return true If the current point coordinates are smaller than the
     * specified point's ones.
     * @return false If the current point coordinates are not smaller than the
     * specified point's ones.
     */
    constexpr bool operator<(const Point& other) const
    {
        constexpr uint8_t bitShift = 24;
        return ((this->x << bitShift) + this->y) <
               ((other.x << bitShift) + other.y);
    }

    /**
     * @brief Less-than-or-equal-to operator.
     *
     * @param other The point to be compared to.
     * @return true If the current point coordinates are smaller or equal than
     * the specified point's ones.
     * @return false If the current point coordinates are greater than the
     * specified point's ones.
     */
    constexpr bool operator<=(const Point& other) const
    {
        return operator==(other) || operator<(other);
    }

    /**
     * @brief Greater-than operator.
     *
     * @param other The point to be compared to.
     * @return true If the current point coordinates are greater than the
     * specified point's ones.
     * @return false If the current point coordinates are smaller than or equal
     * the specified point's ones.
     */
    constexpr bool operator>(const Point& other) const
    {
        return !operator<=(other);
    }

    /**
     * @brief Greater-than-or-equal-to operator.
     *
     * @param other The point to be compared to.
     * @return true If the current point coordinates are greater than or equal
     * the specified point's ones.
     * @return false If the current point coordinates are smaller than the
     * specified point's ones.
     */
    constexpr bool operator>=(const Point& other) const
    {
        return !operator<(other);
    }

    /**
     * @brief Returns the Mahnattan distance between this point and the
     * specified one.
     *
     * @param other The point to which the distance should be calculated.
     * @return constexpr uint32_t The Manhattan distance between the two points.
     */
    constexpr uint32_t Distance(const Point& other) const
    {
        return std::abs(this->x - other.x) + std::abs(this->y - other.y);
    }
};

/**
 * @brief Stream extraction operator.
 *
 * @param out An output stream instance.
 * @param p The point to be represented as string stream.
 * @return std::ostream& A reference to the specified stream.
 */
static std::ostream& operator<<(std::ostream& out, const Point& p)
{
    return out << '(' << p.x << ',' << p.y << ')';
}
}
