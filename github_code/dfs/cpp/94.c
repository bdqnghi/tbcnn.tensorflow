//
//  DepthFirstSearch.cpp
//  PhaseUnwrapping
//
//  Created by Ian Herszterg on 1/17/15.
//  Copyright (c) 2015 Ian Herszterg. All rights reserved.
//

#include "DepthFirstSearch.h"
#include "Residue.h"

void DepthFirstSearch(std::vector<Point>& points, std::vector<Edge>& edges, Point * start, int groupId, int& nPos, int& nNeg, bool& borderFound)
{
    start->group_n = groupId;
    start->visited = true;
    
    if(start->isBorder)
        borderFound = true;
    else if(start->type == POS_RESIDUE)
        nPos++;
    else if(start->type == NEG_RESIDUE)
        nNeg++;
    
    for( unsigned int i = 0; i < edges.size(); i++ )
    {
        if(!edges[i].valid)
            continue;
        
        Point * destination;
        
        if( (edges[i].p1->i == start->i && edges[i].p1->j == start->j) || (edges[i].p2->i == start->i && edges[i].p2->j == start->j))
        {
            if( (edges[i].p1->i == start->i && edges[i].p1->j == start->j))
                destination = edges[i].p2;
            else
                destination = edges[i].p1;
            
            if(!destination->visited && !edges[i].visited)
            {
                edges[i].visited = true;
                DepthFirstSearch(points, edges, destination, groupId, nPos, nNeg, borderFound);
            }
        }
    }
}

int FindDisconnectedPieces( std::vector<Point>& points, std::vector<Edge>& edges, bool disconect )
{
    int groups = -1;
    
    for( unsigned int i = 0; i < points.size(); i++ )
    {
        if( !points[i].visited )
        {
            groups++;
            bool borderFound = false;
            
            int nPos = 0, nNeg = 0;
            DepthFirstSearch( points, edges, &points[i], groups, nPos, nNeg, borderFound);
            
            if(disconect && nPos != nNeg && !borderFound)
                return -1;
        }
    }
    
    return groups;
}
