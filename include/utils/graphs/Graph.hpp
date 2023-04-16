#pragma once

#include "Node.hpp"
#include "Edge.hpp"
#include "utils/graphs/Node.hpp"

#include <map>

namespace AdventOfCode::Utils::Graphs
{
template <typename NodeValue = int, typename EdgeWeight = int>
requires (std::integral<NodeValue> || std::floating_point<NodeValue>) 
      && (std::integral<EdgeWeight> || std::floating_point<EdgeWeight>)
class Graph
{
  public:
    using node_type = Node<NodeValue, EdgeWeight>;
    using edge_type = Edge<NodeValue, EdgeWeight>;

    void AddNode(const typename node_type::name_type& nodeName, NodeValue nodeValue) noexcept
    {
        m_nodes[nodeName] = Node<NodeValue, EdgeWeight>{nodeName, nodeValue};
    }

    void AddEdge(const typename node_type::name_type& fromNodeName, NodeValue fromNodeValue, const typename node_type::name_type& toNodeName, NodeValue toNodeValue, const EdgeWeight& edgeWeight)
    {
        if (!m_nodes.contains(fromNodeName))
        {
            AddNode(fromNodeName, fromNodeValue);
        }
        else 
        {
            m_nodes[fromNodeName].SetValue(fromNodeValue);
        }

        if (!m_nodes.contains(toNodeName))
        {
            AddNode(toNodeName, toNodeValue);
        }
        else 
        {
            m_nodes[toNodeName].SetValue(toNodeValue);
        }

        m_nodes[fromNodeName].ConnectTo(&m_nodes.at(toNodeName), edgeWeight);
    }

    void AddEdge(const typename node_type::name_type& fromNodeName, const typename node_type::name_type& toNodeName, const EdgeWeight& edgeWeight)
    {
        AddEdge(fromNodeName, 0, toNodeName, 0, edgeWeight);
    }

    [[nodiscard]] std::map<typename node_type::name_type, node_type> GetNodes() const
    {
        return m_nodes;
    }

    [[nodiscard]] const node_type& GetNode(const typename node_type::name_type& nodeName) const
    {
        return m_nodes.at(nodeName);
    }

    [[nodiscard]] const edge_type& GetEdge(const typename node_type::name_type& fromNodeName, const typename node_type::name_type& toNodeName) const
    {
        const auto& node = GetNode(fromNodeName);
        for (const auto& e : node.GetEdges())
        {
            if (e.to->GetName() == toNodeName)
            {
                return e;
            }
        }
    }

  private:
    std::map<typename node_type::name_type, node_type> m_nodes;
};
} // namespace AdventOfCode::Utils::Graphs