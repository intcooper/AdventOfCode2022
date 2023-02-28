#include "Day15.h"
#include "utils/Line.hpp"
#include "utils/Helpers.hpp"
#include <algorithm>
#include <stdint.h>
#include <string>

namespace AdventOfCode
{
Day15::Day15(std::string inputFileName, std::string params)
    : DailyTask(inputFileName, params)
{
}

void Day15::Task1()
{
    ParseInputFile();

    const auto param = Utils::Split(m_params, ' ')[0].data();
    const int row = std::stoi(param) - m_minPoint.y;
    uint32_t nonValidCount{0};

    const auto cols = m_maxPoint.x - m_minPoint.x;

    for (auto x = 0; x < cols; x++)
    {
        const Utils::Point current{x, row};

        for (const auto& sb : m_sensorsAndBeacons)
        {
            const auto sensor = sb.first - m_minPoint;
            const auto beacon = sb.second - m_minPoint;

            if ((sensor == current) || (beacon == current))
            {
                break;
            }

            const auto beaconDistance = sensor.Distance(beacon);
            const auto currentDistance = sensor.Distance(current);

            if (currentDistance <= beaconDistance)
            {
                nonValidCount++;
                break;
            }
        }
    }

    m_result = std::to_string(nonValidCount);
}

void Day15::Task2()
{
    ParseInputFile();

    std::vector<Utils::Line> edges1;
    std::vector<Utils::Line> edges2;

    // Populate the edges collections in form of lines.
    // The points are the vertices of the polygon defining the boundaries of the
    // sensor detection area.
    // The polygon itself lies just outside of the detection area.
    // Therefore the vertices are defined as follows:
    //   PN = (Sx, Sy - Ed)
    //   PS = (Sx, Sy + Ed)
    //   PW = (Sx - Ed, Sy)
    //   PN = (Sx + Ed, Sy)
    // Where (Sx, Sy) are the Sensor's coordinates and Ed is the Edge distance,
    // which is the Beacon distance + 1.
    // The first collection includes the pairs N-E and S-W.
    // The second collection includes the pairs N-W and S-E.
    for (const auto& sb : m_sensorsAndBeacons)
    {
        const auto sensor = sb.first;
        const auto beacon = sb.second;

        const auto beaconDistance = sensor.Distance(beacon);
        const auto edgeDistance = static_cast<int>(beaconDistance + 1);

        const auto pn = Utils::Point{sensor.x, sensor.y - edgeDistance};
        const auto ps = Utils::Point{sensor.x, sensor.y + edgeDistance};
        const auto pe = Utils::Point{sensor.x + edgeDistance, sensor.y};
        const auto pw = Utils::Point{sensor.x - edgeDistance, sensor.y};

        edges1.emplace_back(pn, pe);
        edges1.emplace_back(ps, pw);
        edges2.emplace_back(pn, pw);
        edges2.emplace_back(ps, pe);
    }

    // find all the intersections between the edges that are between the defined
    // coordinates range.
    // The map counts how many times the same intersection has been found.
    const auto param = Utils::Split(m_params, ' ')[1].data();
    const int maxCoord = std::stoi(param);
    std::map<Utils::Point, int> intersections;

    for (const auto& e1 : edges1)
    {
        for (const auto& e2 : edges2)
        {
            const auto pi = e1.Intersect(e2);

            if ((pi.x >= 0) && (pi.x <= maxCoord) && (pi.y >= 0) && (pi.y <= maxCoord))
            {
                intersections[pi] = intersections[pi] + 1;
            }
        }
    }

    // find the only intersection that lies outside of all the sensors detection
    // areas.
    Utils::Point distressBeacon{-1, -1};

    for (const auto& i : intersections)
    {
        if (i.second < 2)
        {
            continue;
        }

        const auto point = i.first;

        const auto res =
            std::ranges::all_of(m_sensorsAndBeacons, [this, point](auto sb) {
                const auto& sensor = sb.first;
                const auto& beacon = sb.second;

                const auto beaconDistance = sensor.Distance(beacon);

                if (beaconDistance >= sensor.Distance(point))
                {
                    return false;
                }

                return true;
            });

        if (res)
        {
            distressBeacon = point;
            break;
        }
    }

    uint64_t tuningFrequency{
        (static_cast<uint64_t>(distressBeacon.x) * 4'000'000ull) +
        static_cast<uint64_t>(distressBeacon.y)};
    m_result = std::to_string(tuningFrequency);
}

void Day15::ParseInputFile()
{
    m_sensorsAndBeacons.clear();

    for (std::string line; std::getline(m_inputFile, line);)
    {
        if (line.empty())
        {
            continue;
        }

        Utils::Point sensor{0, 0};
        Utils::Point beacon{0, 0};
        Utils::Point* currentPoint = nullptr;

        const auto parts = Utils::Split(line, ':');

        for (const auto& p : parts)
        {
            if (p.starts_with("Sensor"))
            {
                currentPoint = &sensor;
            }

            if (p.find("beacon") != std::string::npos)
            {
                currentPoint = &beacon;
            }

            const auto obj_parts = Utils::Split(p, ' ');

            for (const auto& op : obj_parts)
            {
                const auto coords_parts = Utils::Split(op, '=');

                if (op.starts_with('x'))
                {
                    currentPoint->x = std::stoi(coords_parts[1].data());
                }

                if (op.starts_with('y'))
                {
                    currentPoint->y = std::stoi(coords_parts[1].data());
                }
            }

            if (currentPoint->x < m_minPoint.x)
                m_minPoint.x = currentPoint->x;
            if (currentPoint->y < m_minPoint.y)
                m_minPoint.y = currentPoint->y;

            if (currentPoint->x > m_maxPoint.x)
                m_maxPoint.x = currentPoint->x;
            if (currentPoint->y > m_maxPoint.y)
                m_maxPoint.y = currentPoint->y;
        }

        m_sensorsAndBeacons[sensor] = beacon;
    }

    for (const auto& sb : m_sensorsAndBeacons)
    {
        const auto sensor = sb.first;
        const auto beacon = sb.second;

        const auto beaconDistance = sensor.Distance(beacon);

        Utils::Point west{static_cast<int>(sensor.x - beaconDistance), sensor.y};
        Utils::Point east{static_cast<int>(sensor.x + beaconDistance), sensor.y};

        Utils::Point north{sensor.x, static_cast<int>(sensor.y - beaconDistance)};
        Utils::Point south{sensor.x, static_cast<int>(sensor.y + beaconDistance)};

        if (west.x < m_minPoint.x)
            m_minPoint.x = west.x;
        if (east.x > m_maxPoint.x)
            m_maxPoint.x = east.x;
        if (north.y < m_minPoint.y)
            m_minPoint.y = north.y;
        if (south.y > m_maxPoint.y)
            m_maxPoint.y = south.y;
    }
}
}