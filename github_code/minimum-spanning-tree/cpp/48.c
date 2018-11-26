#include <unordered_set> //For keeping track if the tree is spanning yet.
#include <queue> //For priority_queue.
#include <sstream> //For stringstream.

#include "MinimumSpanningTree.h"

MinimumSpanningTree::Edge::Edge(const Point* start, const Point* end) : start(start), end(end) {
    //Just store the two endpoints.
}

int MinimumSpanningTree::Edge::length() const {
    return start->distance(*end);
}

struct CompareEdges {
    bool operator()(MinimumSpanningTree::Edge& left, MinimumSpanningTree::Edge& right) {
        return left.length() > right.length();
    }
};

MinimumSpanningTree::MinimumSpanningTree(const std::vector<Point>& vertices) : vertices(vertices) {
    //We want to create a minimum spanning tree of the complete graph of all of these vertices, so first generate all edges.
    std::priority_queue<Edge, std::vector<Edge>, CompareEdges> complete_edges;
    for(size_t i = 0; i < vertices.size(); i++) {
        for(size_t j = 0; j < i; j++) {
            complete_edges.push(Edge(&vertices[i], &vertices[j]));
        }
    }

    //Implementation of Prim's algorithm: Keep drawing edges from a priority queue until the graph is strongly connected.
    std::unordered_set<const Point*> spanned_vertices; //All vertices that are currently in the minimum spanning tree. If this is equal to the total size of the vertices, we've got a MST.
    while(!complete_edges.empty() && spanned_vertices.size() < vertices.size()) {
        Edge edge = Edge(complete_edges.top());
        complete_edges.pop();
        edges.push_back(edge);
        spanned_vertices.insert(edge.start);
        spanned_vertices.insert(edge.end);
    }
}

std::string MinimumSpanningTree::toSVG() {
    std::stringstream result;

    //Header.
    result << "<svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 100 100\">\n";

    //Draw every edge first, below the vertices.
    for(Edge edge : edges) {
        result << "\t<line x1=\"" << edge.start->x << "\" y1=\"" << edge.start->y << "\" x2=\"" << edge.end->x << "\" y2=\"" << edge.end->y << "\" stroke=\"red\" stroke-width=\"1\" />\n";
    }

    //Draw every vertex as a circle.
    for(Point vertex : vertices) {
        result << "\t<circle cx=\"" << vertex.x << "\" cy=\"" << vertex.y << "\" r=\"1\" />\n";
    }

    //Footer.
    result << "</svg>";

    return result.str();
}