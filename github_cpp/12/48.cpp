#include <unordered_set> 
#include <queue> 
#include <sstream> 

#include "MinimumSpanningTree.h"

MinimumSpanningTree::Edge::Edge(const Point* start, const Point* end) : start(start), end(end) {
    
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
    
    std::priority_queue<Edge, std::vector<Edge>, CompareEdges> complete_edges;
    for(size_t i = 0; i < vertices.size(); i++) {
        for(size_t j = 0; j < i; j++) {
            complete_edges.push(Edge(&vertices[i], &vertices[j]));
        }
    }

    
    std::unordered_set<const Point*> spanned_vertices; 
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

    
    result << "<svg xmlns=\"http:

    
    for(Edge edge : edges) {
        result << "\t<line x1=\"" << edge.start->x << "\" y1=\"" << edge.start->y << "\" x2=\"" << edge.end->x << "\" y2=\"" << edge.end->y << "\" stroke=\"red\" stroke-width=\"1\" />\n";
    }

    
    for(Point vertex : vertices) {
        result << "\t<circle cx=\"" << vertex.x << "\" cy=\"" << vertex.y << "\" r=\"1\" />\n";
    }

    
    result << "</svg>";

    return result.str();
}