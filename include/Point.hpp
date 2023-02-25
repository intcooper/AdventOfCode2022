#pragma once

#include <algorithm>
#include <optional>
#include <ostream>

namespace AdventOfCode
{
struct Point
{
    int x;
    int y;

    constexpr Point()
        : x{0}
        , y{0}
    {
    }

    virtual constexpr ~Point(){};

    constexpr Point(int x1, int y1)
        : x{x1}
        , y{y1}
    {
    }

    constexpr Point(const Point& other)
        : x{other.x}
        , y{other.y}
    {
    }

    Point(Point&& other) noexcept
        : x{other.x}
        , y{other.y}
    {
    }

    Point& operator=(const Point& other)
    {
        return *this = Point(other);
    }

    Point& operator=(Point&& other) noexcept
    {
        std::swap(x, other.x);
        std::swap(y, other.y);
        return *this;
    }

    constexpr bool operator==(const Point& other) const
    {
        return this->x == other.x && this->y == other.y;
    }

    constexpr bool operator!=(const Point& other) const
    {
        return !operator==(other);
    }

    constexpr Point operator-(const Point& other) const
    {
        return {this->x - other.x, this->y - other.y};
    }

    constexpr Point operator-(int i) const
    {
        return {this->x - i, this->y - i};
    }

    constexpr Point operator+(const Point& other) const
    {
        return {this->x + other.x, this->y + other.y};
    }

    constexpr Point operator*(int i) const
    {
        return {this->x * i, this->y * i};
    }

    constexpr Point& operator+=(const Point& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    Point& operator/=(const Point& other)
    {
        this->x /= std::abs(other.x == 0 ? 1 : other.x);
        this->y /= std::abs(other.y == 0 ? 1 : other.y);

        return *this;
    }

    constexpr bool operator<(const Point& other) const
    {
        constexpr uint8_t bitShift = 24;
        return ((this->x << bitShift) + this->y) <
               ((other.x << bitShift) + other.y);
    }

    constexpr bool operator<=(const Point& other) const
    {
        return operator==(other) || operator<(other);
    }

    constexpr bool operator>(const Point& other) const
    {
        return !operator==(other) && !operator<(other);
    }

    constexpr bool operator>=(const Point& other) const
    {
        return operator==(other) || operator>(other);
    }

    // Returns the Mahnattan distance between this point and the specified one.
    constexpr uint32_t Distance(const Point& other) const
    {
        return std::abs(this->x - other.x) + std::abs(this->y - other.y);
    }
};

static std::ostream& operator<<(std::ostream& out, const Point& p)
{
    return out << '(' << p.x << ',' << p.y << ')';
}
}
