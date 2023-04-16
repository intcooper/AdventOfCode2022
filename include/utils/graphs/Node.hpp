#pragma once

#include "Edge.hpp"

#include <string>
#include <string_view>
#include <vector>

namespace AdventOfCode::Utils::Graphs
{

template <typename NodeValue = int, typename EdgeWeight = int>
requires (std::integral<NodeValue> || std::floating_point<NodeValue>) 
      && (std::integral<EdgeWeight> || std::floating_point<EdgeWeight>)
class Node
{
  public:
    using name_type = std::string;
    using value_type = NodeValue;
    using edge_weight_type = EdgeWeight;

    Node()
    : m_name{}
    , m_value{0}
    , m_edges()
    {
    }

    Node(std::string_view name, NodeValue value)
    : m_name{name}
    , m_value{value}
    , m_edges()
    {
    }

    explicit Node(std::string_view name)
    : Node(name, 0)
    {
    }

    [[nodiscard]] const name_type& GetName() const
    {
        return m_name;
    }

    void SetName(const name_type& name)
    {
        m_name = name;
    }

    [[nodiscard]] const value_type& GetValue() const
    {
        return m_value;
    }

    void SetValue(const value_type& value)
    {
        m_value = value;
    }

    [[nodiscard]] const std::vector<Edge<NodeValue, EdgeWeight>>& GetEdges() const
    {
        return m_edges;
    }

    void ConnectTo(const Node<NodeValue, EdgeWeight>* neighbour, const EdgeWeight& weight)
    {
        m_edges.emplace_back(this, neighbour, weight);
    }

  private:
    name_type m_name;
    value_type m_value;
    std::vector<Edge<value_type, edge_weight_type>> m_edges;
};
} // namespace AdventOfCode::Utils::Graphs