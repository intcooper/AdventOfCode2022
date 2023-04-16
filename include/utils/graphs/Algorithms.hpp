#pragma once

#include "Graph.hpp"
#include <deque>
#include <functional>
#include <limits>
#include <map>
#include <set>

namespace AdventOfCode::Utils::Graphs
{

// A* path-finding algorithm
template <typename NodeValue = int, typename EdgeWeight = int>
requires(std::integral<NodeValue> || std::floating_point<NodeValue>) &&
        (std::integral<EdgeWeight> || std::floating_point<EdgeWeight>)
std::list<Edge<NodeValue, EdgeWeight>> AStar(
        const Graph<NodeValue, EdgeWeight>& graph, 
        const typename Graph<NodeValue, EdgeWeight>::node_type::name_type& start, 
        const typename Graph<NodeValue, EdgeWeight>::node_type::name_type& end,
        std::function<int(const typename Graph<NodeValue, EdgeWeight>::node_type&, const typename Graph<NodeValue, EdgeWeight>::node_type&)> heuristic)
{
    using GraphNode = typename Graph<NodeValue, EdgeWeight>::node_type;
    std::vector<GraphNode> outPath;

    struct AStarNode
    {
        AStarNode(const GraphNode& node, const GraphNode& parent, int f, int g, int h)
            : node{node}
            , parent{parent}
            , f{f}
            , g{g}
            , h{h}
        {
        }

        GraphNode node;
        GraphNode parent;
        int f; // g + h
        int g; // total cost of path from the start to this node
        int h; // heuristic result (estimated distance/cost from destination)
    };

    std::map<typename GraphNode::name_type, AStarNode> open;
    std::map<typename GraphNode::name_type, AStarNode> closed;

    AStarNode openNode{graph.GetNode(start), GraphNode{}, 0, 0, 0};
    open[openNode.node.GetName()] = openNode;

    while (!open.empty())
    {
        uint32_t minimumDistance{std::numeric_limits<uint32_t>::max()};
        typename GraphNode::name_type minimumDistanceNodeName;

        for (const auto& p : open)
        {
            if (static_cast<uint32_t>(p.second.f) < minimumDistance)
            {
                minimumDistance = p.second.f;
                minimumDistanceNodeName = p.first;
            }
        }

        auto currentNode = open.at(minimumDistanceNodeName);

        open.erase(minimumDistanceNodeName);

        closed.insert({currentNode.node.GetName(), currentNode});

        if (currentNode.node.GetName() == end)
        {
            // return path
            auto current = currentNode;
            while (!current.parent.GetName().empty())
            {
                outPath.emplace_back(current.node.GetName());
                current = closed.at(current.parent.GetName());
            }

            break;
        }

        for (const auto& e : currentNode.node.GetEdges())
        {
            auto closedNode = closed.find(e.to->GetName());

            if (closedNode != closed.end())
            {
                // skip the point because already in the closed list
                continue;
            }

            const auto g = currentNode.g + 1;
            const auto h = heuristic(graph.GetNode(end), graph.GetNode(e.to->GetName()));
            const auto f = g + h;
            const auto nextNode = AStarNode{e.to, currentNode.node, f, g, h};

            auto openNode = open.find(nextNode.node.GetName());

            if (openNode != open.end())
            {
                if (openNode->second.g > nextNode.g)
                {
                    open.erase(openNode.first);
                    open[nextNode.node.GetName()] = nextNode;
                }
            }
            else
            {
                open[nextNode.node.GetName()] = nextNode;
            }
        }
    }

    return outPath;
}

template <typename NodeValue = int, typename EdgeWeight = int>
requires (std::integral<NodeValue> || std::floating_point<NodeValue>) &&
         (std::integral<EdgeWeight> || std::floating_point<EdgeWeight>)
std::list<Edge<NodeValue, EdgeWeight>> BreadthFirstSearch(
    const Graph<NodeValue, EdgeWeight>& graph, 
    const typename Node<NodeValue, EdgeWeight>::name_type& start, 
    const typename Node<NodeValue, EdgeWeight>::name_type& end)
{
    using GraphNode = typename Graph<NodeValue, EdgeWeight>::node_type;

    std::deque<const GraphNode*> frontier;
    std::map<typename GraphNode::name_type, typename GraphNode::name_type> visited;

    const GraphNode* currentValve;
    frontier.emplace_back(&start);
    visited[start] = "";

    while (!frontier.empty())
    {
        currentValve = frontier.front();
        frontier.pop_front();

        if (currentValve->GetName() == end)
        {
            break;
        }

        for (const auto& e : currentValve->GetEdges())
        {
            const auto& neighbour = e.to;
            if (!visited.contains(neighbour->GetName()))
            {
                visited[neighbour->GetName()] = currentValve->GetName();
                frontier.push_back(neighbour);
            }
        }
    }

    std::list<Edge<NodeValue, EdgeWeight>> path;
    auto currentValveName = currentValve->GetName();
    while (currentValveName != start)
    {
        path.emplace_back(graph.GetEdge(currentValveName, visited.at(currentValveName)));
        currentValveName = visited.at(currentValveName);
    }

    return path;
}

template <typename NodeValue = int, typename EdgeWeight = int>
requires (std::integral<NodeValue> || std::floating_point<NodeValue>) &&
         (std::integral<EdgeWeight> || std::floating_point<EdgeWeight>)
std::list<Edge<NodeValue, EdgeWeight>> Dijkstra(
        const Graph<NodeValue, EdgeWeight>& graph, 
        const typename Graph<NodeValue, EdgeWeight>::node_type::name_type& start, 
        const typename Graph<NodeValue, EdgeWeight>::node_type::name_type& end)
{
    using GraphNode = typename Graph<NodeValue, EdgeWeight>::node_type;

    std::map<typename GraphNode::name_type, uint32_t> distances;
    std::map<typename GraphNode::name_type, typename GraphNode::name_type> prev;
    std::set<GraphNode> open;

    for (const auto& node : graph.GetNodes())
    {
        distances.push_back(std::numeric_limits<uint32_t>::infinity());
        prev.push_back();
        open.push_back(node);
    }

    distances[start.GetName()] = 0;

    while (!open.empty())
    {
        const auto& currentNode = open.begin();
        open.erase(open.begin());

        if (currentNode == end)
        {
            break;
        }

        for (const auto& neighbour : currentNode.GetEdges())
        {
            size_t alt = distances[currentNode.GetName()] + neighbour.GetWeight();
            if (alt < distances[neighbour.GetName()])
            {
                distances[neighbour.GetName()] = alt;
                prev[neighbour.GetName()] = currentNode.GetName();
            }
        }
    }

    std::list<Edge<NodeValue, EdgeWeight>> path;
    typename GraphNode::name_type currentNodeName = end.GetName();
    while (prev.at(currentNodeName) != prev.end())
    {
        path.push_front(prev.at(currentNodeName));
        currentNodeName = prev.at(currentNodeName);
    }

    return path;
}

} // namespace AdventOfCode::Utils::Graphs