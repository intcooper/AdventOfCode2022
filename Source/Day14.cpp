#include "Day14.h"
#include <iostream>
#include <optional>
#include <stdint.h>
#include <string>
#include <array>

//#define PRINTMAP


namespace AdventOfCode
{
    Day14::Day14(std::string inputFileName)
    : DailyTask(inputFileName)
	{
	}

    void Day14::Task1()
    {
        ParseInputFile();

        auto sourceX = std::find(m_map.row_begin(0), m_map.row_end(0), '+');
        Point source{static_cast<int>(std::distance(m_map.row_begin(0), sourceX)), 0};

        PrintMap(source);

        auto units = DropSand(source);
        m_result = std::to_string(units);
    }

    void Day14::Task2()
    {
        ParseInputFile();

        int total_units = 0;

        m_map.Resize(m_map.Rows() + 2, m_map.Cols(), '.');
        PlotSegment({0, static_cast<int>(m_map.Rows() - 1)}, {static_cast<int>(m_map.Cols() - 1), static_cast<int>(m_map.Rows() - 1)});

        auto sourceX = std::find(m_map.row_begin(0), m_map.row_end(0), '+');
        Point source{static_cast<int>(std::distance(m_map.row_begin(0), sourceX)), 0};

        while (true)
        {
            m_sandUnit = source;
            auto units = DropSand(source);
            total_units += units;

            PrintMap(source);

            if (m_sandUnit == source)
            {
                break;
            }

            m_map.Resize(m_map.Rows(), m_map.Cols() + 2, '.');
            PlotSegment({0, static_cast<int>(m_map.Rows() - 1)}, {static_cast<int>(m_map.Cols() - 1), static_cast<int>(m_map.Rows() - 1)});
            
            sourceX = std::find(m_map.row_begin(0), m_map.row_end(0), '+');
            source = Point{static_cast<int>(std::distance(m_map.row_begin(0), sourceX)), 0};
        }

        m_result = std::to_string(total_units);
    }

    void Day14::PlotSegment(const Point& start, const Point& end)
    {
        auto s = std::min(start, end);
        auto e = std::max(start, end);

        for (auto y = s.y; y <= e.y; ++y)
        {
            for (auto x = s.x; x <= e.x; ++x)
            {
                m_map.Set(y, x, '#');
            }
        }
    }

    void Day14::PrintMap(const Point& source)
    {
        #ifdef PRINTMAP
        std::cout << '\n';

        std::cout << source << std::endl;

        for (auto y = 0; y < m_map.Rows(); ++y)
        {
            for (auto x = 0; x < m_map.Cols(); ++x)
            {
                std::cout << m_map.Get(y, x).value();
            }

            std::cout << '\n';
        }

        std::cout << std::endl;
        #endif
    }

    void Day14::ParseInputFile()
    {
        std::vector<std::vector<Point>> points;
            
        for (std::string line; std::getline(m_inputFile, line); )
        {
            if (line.empty())
            {
                continue;
            }

            points.emplace_back();

            const auto parts = Utils::Split(line, ' ');

            for (const auto& p : parts)
            {
                if (p.starts_with("-"))
                {
                    continue;
                }

                auto coordsStr = Utils::Split(p, ',');

                auto x = std::stoi(coordsStr[0].data());
                auto y = std::stoi(coordsStr[1].data());
                points.back().emplace_back(x, y);

                if (x < m_minPoint.x) m_minPoint.x = x;
                if (x > m_maxPoint.x) m_maxPoint.x = x;
                if (y < m_minPoint.y) m_minPoint.y = y;
                if (y > m_maxPoint.y) m_maxPoint.y = y;
            }
        }

        m_map.SetSize(m_maxPoint.y - m_minPoint.y + 1, m_maxPoint.x - m_minPoint.x + 1, '.');

        for (auto& p : points)
        {
            int i = 0;
    
            while (i < p.size() - 1)
            {
                auto start = p[i];
                auto end = p[i + 1];

                start.x -= m_minPoint.x;
                start.y -= m_minPoint.y;

                end.x -= m_minPoint.x;
                end.y -= m_minPoint.y;

                PlotSegment(start, end);

                ++i;
            }
        }

        m_map.Set(0, 500 - m_minPoint.x, '+');
    }

    int Day14::DropSand(Point source)
    {
        int units{0};
        m_sandUnit = source;

        while (true)
        {
            auto nextPoint = Point{m_sandUnit.x, m_sandUnit.y + 1};
            auto nextChar = m_map.Get(nextPoint.y, nextPoint.x);
            
            if (nextChar == '.')
            {
                m_sandUnit = nextPoint;
                continue;    
            }

            nextPoint = Point{m_sandUnit.x - 1, m_sandUnit.y + 1};
            nextChar = m_map.Get(nextPoint.y, nextPoint.x);
            
            if (nextChar == '.')
            {
                m_sandUnit = nextPoint;
                continue;    
            }

            if (nextChar == std::nullopt)
            {
                break;
            }

            nextPoint = Point{m_sandUnit.x + 1, m_sandUnit.y + 1};
            nextChar = m_map.Get(nextPoint.y, nextPoint.x);
            
            if (nextChar == '.')
            {
                m_sandUnit = nextPoint;
                continue;    
            }

            if (nextChar == std::nullopt)
            {
                break;
            }

            m_map.Set(m_sandUnit.y, m_sandUnit.x, 'o');
            ++units;

            if (m_sandUnit == source)
            {
                break;
            }

            m_sandUnit = source;

            //std::cout << units << std::endl;
            //PrintMap();
        }

        //std::cout << units << std::endl;
        //PrintMap();
        return units;
    }
}