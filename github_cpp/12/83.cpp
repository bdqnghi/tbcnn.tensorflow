


#include "MinimumSpanningTree.h"

namespace cura
{

MinimumSpanningTree::MinimumSpanningTree(std::unordered_set<Point> vertices) : adjacency_graph(prim(vertices))
{
    
}

MinimumSpanningTree::Edge::Edge(const Point start, const Point end) : start(start), end(end)
{
    
}

int MinimumSpanningTree::Edge::length() const
{
    return vSize2(start - end);
}

const std::unordered_map<Point, std::vector<MinimumSpanningTree::Edge>> MinimumSpanningTree::prim(std::unordered_set<Point> vertices) const
{
    std::unordered_map<Point, std::vector<Edge>> result;
    if (vertices.empty())
    {
        return result; 
    }
    result.reserve(vertices.size());
    std::vector<Point> vertices_list;
    for (Point vertex : vertices)
    {
        vertices_list.push_back(vertex);
    }

    Point first_point = vertices_list[0];
    result[first_point] = std::vector<MinimumSpanningTree::Edge>(); 

    if (vertices_list.size() == 1)
    {
        return result; 
    }

    std::unordered_map<Point*, coord_t> smallest_distance; 
    smallest_distance.reserve(vertices_list.size());
    std::unordered_map<Point*, Point*> smallest_distance_to; 
    smallest_distance_to.reserve(vertices_list.size());
    for (size_t vertex_index = 0; vertex_index < vertices_list.size(); vertex_index++)
    {
        if (vertices_list[vertex_index] == first_point)
        {
            continue;
        }
        smallest_distance[&vertices_list[vertex_index]] = vSize2(vertices_list[vertex_index] - first_point);
        smallest_distance_to[&vertices_list[vertex_index]] = &vertices_list[0];
    }

    while(result.size() < vertices_list.size()) 
    {
        
        
        
        
        Point* closest_point = nullptr;
        coord_t closest_distance = std::numeric_limits<coord_t>::max();
        for(std::pair<Point*, coord_t> point_and_distance : smallest_distance)
        {
            if (point_and_distance.second < closest_distance) 
            {
                closest_point = point_and_distance.first;
                closest_distance = point_and_distance.second;
            }
        }

        
        Point closest_point_local = *closest_point;
        Point other_end = *smallest_distance_to[closest_point];
        if (result.find(closest_point_local) == result.end())
        {
            result[closest_point_local] = std::vector<Edge>();
        }
        result[closest_point_local].emplace_back(closest_point_local, other_end);
        if (result.find(other_end) == result.end())
        {
            result[other_end] = std::vector<Edge>();
        }
        result[other_end].emplace_back(other_end, closest_point_local);
        smallest_distance.erase(closest_point); 
        smallest_distance_to.erase(closest_point);

        
        for (std::pair<Point*, coord_t> point_and_distance : smallest_distance)
        {
            coord_t new_distance = vSize2(*closest_point - *point_and_distance.first);
            if (new_distance < point_and_distance.second) 
            {
                smallest_distance[point_and_distance.first] = new_distance;
                smallest_distance_to[point_and_distance.first] = closest_point;
            }
        }
    }

    return result;
}

const std::vector<Point> MinimumSpanningTree::adjacentNodes(Point node) const
{
    std::vector<Point> result;
    std::unordered_map<Point, std::vector<Edge>>::const_iterator adjacency_entry = adjacency_graph.find(node);
    if (adjacency_entry != adjacency_graph.end())
    {
        for (const Edge edge : (*adjacency_entry).second)
        {
            
            if (edge.start == node)
            {
                result.push_back(edge.end);
            }
            else
            {
                result.push_back(edge.start);
            }
        }
    }
    return result;
}

std::vector<Point> MinimumSpanningTree::leaves() const
{
    std::vector<Point> result;
    for (std::pair<Point, std::vector<Edge>> node : adjacency_graph)
    {
        if (node.second.size() <= 1) 
        {
            result.push_back(node.first);
        }
    }
    return result;
}

std::vector<Point> MinimumSpanningTree::vertices() const
{
    std::vector<Point> result;
    for (std::pair<Point, std::vector<Edge>> node : adjacency_graph)
    {
        result.push_back(node.first);
    }
    return result;
}

}