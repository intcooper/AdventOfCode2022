#pragma once

#include "DailyTask.h"

#include <string>
#include <string_view>
#include <map>
#include <list>

namespace AdventOfCode
{
template <class ValueType>
class Node
{
  public:
    std::string_view GetName() const
    {
        return m_name;
    }

    void SetName(std::string_view name)
    {
        m_name = name;
    }

    const ValueType& GetValue() const
    {
        return m_value;
    }

    void SetValue(ValueType value)
    {
        m_value = value;
    }

    const std::vector<Node<ValueType>*>& GetChildren() const
    {
        return m_children;
    }

    void AddChild(Node<ValueType>* child)
    {
        m_children.push_back(child);
    }

  private:
    std::string m_name;
    ValueType m_value;
    std::vector<Node<ValueType>*> m_children;
};

using Valve = Node<uint32_t>;
using ValveName = std::string;

class Day16 : public DailyTask
{
  public:
    Day16(std::string inputFileName, std::string params);

    inline virtual std::string GetTitle() const override
    {
        return "Day 16 - Proboscidea Volcanium";
    }

    virtual void Task1() override;
    virtual void Task2() override;

  private:
    std::map<ValveName, Valve> m_valves;

    void ParseInputFile();
    std::vector<ValveName> GetShortestPath(const Valve& valve, const Valve& fromValve);
    std::vector<ValveName> GetNextValvePath(const std::list<ValveName>& closedValves, const Valve& currentValve);
    inline float GetPathScore(std::vector<ValveName>) const;
};
} // namespace AdventOfCode
