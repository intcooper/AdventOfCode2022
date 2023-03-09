#include "Day16.h"
#include "utils/Helpers.hpp"
#include <algorithm>
#include <cmath>
#include <deque>
#include <memory>
#include <set>
#include <stdint.h>
#include <string>

namespace AdventOfCode
{
Day16::Day16(std::string inputFileName, std::string params)
    : DailyTask(inputFileName, params)
{
}

void Day16::Task1()
{
    ParseInputFile();

    int remainingMinutes{30};
    int totalPressure{0};

    Valve* currentValve = &m_valves.at("AA");

    std::vector<std::pair<ValveName, Valve>> orderedMap;

    for (auto v : m_valves)
    {
        if (v.second.GetValue() > 0)
        {
            orderedMap.emplace_back(v.first, v.second);
        }
    }

    std::ranges::sort(orderedMap, [](const auto& a, const auto& b) { return a.second.GetValue() > b.second.GetValue(); });

    std::list<ValveName> closedValvesNames;
    for (const auto& v : orderedMap)
    {
        closedValvesNames.push_back(std::string{v.second.GetName()});
    }

    std::set<ValveName> openValvesNames;
    std::deque<std::string> targets;

    while (remainingMinutes > 0)
    {
        if (!closedValvesNames.empty())
        {
            const auto nextValvePath = GetNextValvePath(closedValvesNames, *currentValve);

            for (size_t i = 0; i < nextValvePath.size(); ++i)
            {
                for (const auto& v : openValvesNames)
                {
                    totalPressure += m_valves.at(ValveName{v}).GetValue();
                }

                --remainingMinutes;
            }

            currentValve = &m_valves.at(nextValvePath.front());
            for (const auto& v : openValvesNames)
            {
                totalPressure += m_valves.at(ValveName{v}).GetValue();
            }
            openValvesNames.insert(nextValvePath.front());
            closedValvesNames.remove(nextValvePath.front());

            --remainingMinutes;
        }
        else
        {
            for (const auto& v : openValvesNames)
            {
                totalPressure += m_valves.at(ValveName{v}).GetValue();
            }

            --remainingMinutes;
        }
    }

    m_result = std::to_string(totalPressure);
}

std::vector<ValveName> Day16::GetNextValvePath(const std::list<ValveName>& closedValves, const Valve& currentValve)
{
    float bestScore{0};
    size_t minPathSize{0};
    std::vector<ValveName> nextValvePath;

    for (const auto& v : closedValves)
    {
        const auto vrate = m_valves.at(v).GetValue();
        const auto path = GetShortestPath(m_valves.at(v), currentValve);
        const auto pathScore = GetPathScore(path);
        
        if (pathScore > bestScore)
        {
            bestScore = pathScore;
            minPathSize = path.size();
            nextValvePath = path;
        }
    }

    return nextValvePath;
}

float Day16::GetPathScore(std::vector<ValveName> path) const
{
    static constexpr float ValveRateWeight{1};
    static constexpr float PathStepsWeight{1};
    float targetValveRate{static_cast<float>(m_valves.at(path[0]).GetValue())};
    float pathSteps{static_cast<float>(path.size())};

    return (targetValveRate * ValveRateWeight) / std::powf(pathSteps * PathStepsWeight, 2.0f);
}

std::vector<ValveName> Day16::GetShortestPath(const Valve& valve, const Valve& fromValve)
{
    std::deque<const Valve*> frontier;
    std::map<ValveName, ValveName> visited;

    const Valve* currentValve;
    frontier.emplace_back(&fromValve);
    visited[std::string(fromValve.GetName())] = "";

    while (!frontier.empty())
    {
        currentValve = frontier.front();
        frontier.pop_front();

        if (currentValve->GetName() == valve.GetName())
        {
            break;
        }

        for (const auto& c : currentValve->GetChildren())
        {
            if (!visited.contains(std::string(c->GetName())))
            {
                visited[std::string(c->GetName())] = currentValve->GetName();
                frontier.push_back(c);
            }
        }
    }

    std::vector<ValveName> path;
    auto currentValveName = currentValve->GetName();
    while (currentValveName != fromValve.GetName())
    {
        path.push_back(ValveName(currentValveName));
        currentValveName = visited.at(ValveName(currentValveName));
    }

    return path;
}

void Day16::Task2() {}

void Day16::ParseInputFile()
{
    for (std::string line; std::getline(m_inputFile, line);)
    {
        const auto parts = Utils::Split(line, ' ');
        const auto name = std::string(parts[1]);
        const auto rate = std::stoi(Utils::Split(parts[4], '=')[1].data());
        auto valvesStr = std::find_if(parts.begin(), parts.end(), [](auto p) { return p.starts_with("valve"); });

        if (!m_valves.contains(name))
        {
            m_valves[name] = Valve();
        }

        Valve& v = m_valves.at(name);
        v.SetName(name);
        v.SetValue(rate);

        valvesStr = std::next(valvesStr);

        while (valvesStr != parts.end())
        {
            const auto childName = std::string((*valvesStr).substr(0, 2));

            if (!m_valves.contains(childName))
            {
                Valve c;
                c.SetName(childName);
                m_valves[childName] = c;
            }

            v.AddChild(&m_valves.at(childName));
            valvesStr = std::next(valvesStr);
        }

        if (!m_valves.contains(name))
        {
            m_valves[name] = v;
        }
    }
}

} // namespace AdventOfCode