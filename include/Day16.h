#pragma once

#include "DailyTask.h"
#include "utils/graphs/Graph.hpp"
#include <list>
#include <set>

namespace AdventOfCode
{

class Day16 : public DailyTask
{
  public:
    Day16(std::string inputFileName, std::string params);

    [[nodiscard]] inline virtual std::string GetTitle() const override
    {
        return "Day 16 - Proboscidea Volcanium";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    using graph_type = Utils::Graphs::Graph<int, int>;
    graph_type m_valves;

    void FindPath(const graph_type::node_type& currentNode, std::list<const graph_type::node_type*> working_valves,
                  std::set<std::string> visited);

    void ParseInputFile();
};
} // namespace AdventOfCode
