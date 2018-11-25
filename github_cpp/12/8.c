#ifndef MINIMUMSPANNINGTREE_H
#define MINIMUMSPANNINGTREE_H

#include <string>
#include <vector>

#include "Point.h"


class MinimumSpanningTree {
public:
    
    std::vector<Point> vertices;

    
    struct Edge {
        
        Edge(const Point* start, const Point* end);

        
        const Point* start;

        
        const Point* end;

        
        int length() const;
    };

    
    std::vector<Edge> edges;

    
    MinimumSpanningTree(const std::vector<Point>& vertices);

    
    std::string toSVG();
};

#endif 