#pragma once

#include "Node.hpp"

#include <string>
#include <vector>

namespace AdventOfCode::Utils::Graphs
{

// Node class forward-declaration
template <typename NodeValue, typename EdgeWeight>
requires(std::integral<NodeValue> || std::floating_point<NodeValue>) &&
        (std::integral<EdgeWeight> || std::floating_point<EdgeWeight>)
class Node;

template <class NodeValue = int, class EdgeWeight = int>
requires(std::integral<NodeValue> || std::floating_point<NodeValue>) &&
        (std::integral<EdgeWeight> || std::floating_point<EdgeWeight>)
struct Edge
{
    Edge()
        : from{}
        , to{}
        , weight{0}
    {
    }

    Edge(const Node<NodeValue, EdgeWeight>* from, const Node<NodeValue, EdgeWeight>* to, const EdgeWeight& weight)
        : from{from}
        , to{to}
        , weight{weight}
    {
    }

    const Node<NodeValue, EdgeWeight>* from;
    const Node<NodeValue, EdgeWeight>* to;
    EdgeWeight weight;
};
} // namespace AdventOfCode::Utils::Graphs