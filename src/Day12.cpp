#include "Day12.h"

#include <algorithm>
#include <array>
#include <map>
#include <ranges>
#include <stdint.h>

namespace AdventOfCode
{
Day12::Day12(std::string inputFileName)
    : DailyTask(inputFileName)
{
}

void Day12::Task1()
{
    ParseInputFile();
    auto shortestPath = Explore(m_startPos, m_endPos);

    m_result = std::to_string(shortestPath.size());
}

void Day12::Task2()
{
    uint32_t shortestPathLength{UINT32_MAX};

    ParseInputFile();

    for (const auto& c : m_candidateStartPos)
    {
        auto shortestPath = Explore(c, m_endPos);
        if ((shortestPath.size() > 0) &&
            (shortestPathLength > shortestPath.size()))
        {
            shortestPathLength = shortestPath.size();
        }
    }

    m_result = std::to_string(shortestPathLength);
}

// A* path-finding algorithm
std::vector<Point> Day12::Explore(const Point& start, const Point& end)
{
    std::vector<Point> outPath;

    struct Node
    {
        Node(Point point, Point parent, int f, int g, int h)
            : point(std::move(point))
            , parent(std::move(parent))
            , f(f)
            , g(g)
            , h(h)
        {
        }

        Node(const Node&) = default;
        Node(Node&&) = default;
        Node& operator=(const Node&) = default;
        Node& operator=(Node&&) = default;

        Point point;
        Point parent;
        int f; // g + h
        int g; // total cost of path from the start to this node
        int h; // heuristic result (estimated distance/cost from destination)
               // - taxicab distance
    };

    constexpr std::array<Point, 4> validDirs = {
        Point{-1, 0}, {+1, 0}, {0, -1}, {0, +1}};

    std::map<Point, Node> open;
    std::map<Point, Node> closed;

    open.insert({start, Node{start, Point{-1, -1}, 0, 0, 0}});

    while (!open.empty())
    {
        uint32_t minimumDistance{UINT32_MAX};
        Point minimumDistancePoint;

        for (const auto& p : open)
        {
            if (p.second.f < minimumDistance)
            {
                minimumDistance = p.second.f;
                minimumDistancePoint = p.first;
            }
        }

        auto currentNode = open.at(minimumDistancePoint);

        open.erase(minimumDistancePoint);

        closed.insert({currentNode.point, currentNode});

        if (currentNode.point == end)
        {
            // return path
            auto current = currentNode;
            while (current.parent.x != -1)
            {
                outPath.emplace_back(current.point);
                current = closed.at(current.parent);
            }

            break;
        }

        auto currentChar = m_map[currentNode.point.y][currentNode.point.x];
        if (currentChar == 'S')
        {
            currentChar = 'a';
        }

        for (const auto& d : validDirs)
        {
            Point next{currentNode.point};
            next += d;

            // check whether the next point has valid coordinates
            if (!((next.y >= 0) && (next.y < m_map.size()) && (next.x >= 0) &&
                  (next.x < m_map[0].size())))
            {
                continue;
            }

            auto closedNode = closed.find(next);

            if (closedNode != closed.end())
            {
                // skip the point because already in the closed list
                continue;
            }

            auto nextChar = m_map[next.y][next.x];

            if (nextChar == 'E')
            {
                nextChar = 'z';
            }

            if ((static_cast<int>(nextChar) - static_cast<int>(currentChar)) >
                1)
            {
                continue;
            }

            const auto g = currentNode.g + 1;
            const auto h = std::abs(m_endPos.y - next.y) +
                           std::abs(m_endPos.x - next.x); // taxicab distance
            const auto f = g + h;
            const auto childNode = Node{next, currentNode.point, f, g, h};

            auto openNode = open.find(childNode.point);

            if (openNode != open.end())
            {
                if (openNode->second.g > childNode.g)
                {
                    open.erase(openNode);
                    open.insert({childNode.point, childNode});
                }
            }
            else
            {
                open.insert({childNode.point, childNode});
            }
        }
    }

    return outPath;
}

void Day12::ParseInputFile()
{
    m_map.clear();
    m_candidateStartPos.clear();

    uint8_t currentRow;

    for (std::string line; std::getline(m_inputFile, line);)
    {
        m_map.push_back(line);
        auto pos = std::find(line.begin(), line.end(), 'S');
        if (pos != line.end())
        {
            m_startPos = Point(pos - line.begin(), currentRow);
        }

        pos = std::find(line.begin(), line.end(), 'E');
        if (pos != line.end())
        {
            m_endPos = Point(pos - line.begin(), currentRow);
        }

        pos = std::find(line.begin(), line.end(), 'a');
        if (pos != line.end())
        {
            m_candidateStartPos.emplace_back(pos - line.begin(), currentRow);
        }

        currentRow++;
    }
}
}
