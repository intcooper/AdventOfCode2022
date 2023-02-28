#pragma once

#include "Point.hpp"
#include <map>
#include <set>
#include <vector>

namespace AdventOfCode::Utils
{
class Rope
{
  public:
    static constexpr Point up{0, 1};
    static constexpr Point down{0, -1};
    static constexpr Point right{1, 0};
    static constexpr Point left{-1, 0};

    Rope()
        : m_head{0, 0}
        , m_tails{}
        , m_visited{}
    {
    }

    explicit Rope(uint8_t nofTails) noexcept
        : m_head{0, 0}
        , m_tails{}
        , m_visited{}
    {
        for (size_t i = 0; i < nofTails; i++)
        {
            m_tails.emplace_back(0, 0);
        }

        m_visited.emplace(0, 0);
    }

    constexpr void MoveHead(Point d, int steps)
    {
        for (size_t i = 0; i < steps; i++)
        {
            m_head += d;

            auto head = m_head;

            for (size_t t = 0; t < m_tails.size(); t++)
            {
                auto distance = head - m_tails[t];

                if ((std::abs(distance.x) == 2) || (std::abs(distance.y) == 2))
                {
                    distance /= distance;

                    m_tails[t] += distance;

                    if (t == m_tails.size() - 1)
                    {
                        m_visited.insert(m_tails[t]);
                    }
                }

                head = m_tails[t];
            }
        }
    }

    const std::set<Point>& GetVisited() const
    {
        return m_visited;
    }

  private:
    Point m_head;
    std::vector<Point> m_tails;
    std::set<Point> m_visited;
};
}