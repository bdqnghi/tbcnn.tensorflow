#include "DepthFirstSearch.h"

#include <exception>
#include <queue>

using namespace std;


namespace
{
    bool DepthFirstSearch(
        const Graph& graph,
        size_t fromVertex,
        size_t toVertex,
        vector<unsigned char>& processed,
        vector<size_t>& result)
    {
        if (fromVertex == toVertex)
        {
            return true;
        }

        processed[fromVertex] = 1;
        const auto& adjacentVertices = graph.GetAdjacent(fromVertex);
        for (auto it = std::begin(adjacentVertices); it != std::end(adjacentVertices); ++it)
        {
            const auto currentAdjacentVertex = *it;
            if (processed[currentAdjacentVertex] == 1)
            {
                continue;
            }

            if (DepthFirstSearch(graph, currentAdjacentVertex, toVertex, processed, result))
            {
                result.push_back(currentAdjacentVertex);
                return true;
            }
        }

        return false;
    }
}


vector<size_t> DepthFirstSearch(const Graph& graph, size_t fromVertex, size_t toVertex)
{
    const auto verticesNumber = graph.GetVerticesNumber();
    if (fromVertex >= verticesNumber || toVertex >= verticesNumber)
    {
        // TODO Add more data to explanation
        throw std::exception("Bad input");
    }

    vector<unsigned char> processed(verticesNumber);
    for_each(begin(processed), end(processed), [](unsigned char& c) { c = 0; });

    vector<size_t> result;
    
    if (DepthFirstSearch(graph, fromVertex, toVertex, processed, result))
    {
        result.push_back(fromVertex);
        return vector<size_t>(result.rbegin(), result.rend());
    }

    return vector<size_t>();
}
