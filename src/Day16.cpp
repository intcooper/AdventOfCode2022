#include "Day16.h"
#include "utils/Helpers.hpp"
#include "utils/graphs/Algorithms.hpp"
#include <deque>

namespace AdventOfCode
{
Day16::Day16(std::string inputFileName, std::string params)
    : DailyTask(inputFileName, params)
{
}

void Day16::Task1()
{
    ParseInputFile();

    std::list<const graph_type::node_type*> working_valves;
    std::set<std::string> visited;

    for (const auto& v : m_valves.GetNodes())
    {
        if (v.second.GetValue() > 0)
        {
            working_valves.push_back(&v.second);
        }
    }

    auto currentNode = m_valves.GetNode("AA");

    // m_result = std::to_string(maxPressure);
}

void Day16::FindPath(const graph_type::node_type& currentNode, std::list<const graph_type::node_type*> working_valves,
                     std::set<std::string> visited)
{
    std::list<std::string> to_visit;

    for (const auto& v : working_valves)
    {
        if (!visited.contains(std::string{v->GetName()}))
        {
            //const auto path = Utils::Graphs::BreadthFirstSearch(m_valves, currentNode.GetName(), v->GetName());
        }
    }
}


void Day16::Task2() {}

void Day16::ParseInputFile()
{
    for (std::string line; std::getline(m_inputFile, line);)
    {
        const auto parts = Utils::Split(line, ' ');
        const auto fromName = std::string(parts[1]);
        const auto fromRate = std::stoi(Utils::Split(parts[4], '=')[1].data());
        auto valvesStr = std::find_if(parts.begin(), parts.end(), [](auto p) { return p.starts_with("valve"); });

        valvesStr = std::next(valvesStr);

        while (valvesStr != parts.end())
        {
            const auto toName = std::string((*valvesStr).substr(0, 2));
            m_valves.AddEdge(fromName, fromRate, toName, 0, 0);
            valvesStr = std::next(valvesStr);
        }
    }
}

} // namespace AdventOfCode