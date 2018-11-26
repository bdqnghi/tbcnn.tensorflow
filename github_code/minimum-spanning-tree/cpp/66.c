//
//  MinimumSpanningTree.cpp
//  PhaseUnwrapping
//
//  Created by Ian Herszterg on 1/17/15.
//  Copyright (c) 2015 Ian Herszterg. All rights reserved.
//

#include "MinimumSpanningTree.h"

bool sortFunction( Edge e1, Edge e2 )
{
    return (e1.cost < e2.cost);
}

MinimumSpanningTree::MinimumSpanningTree( std::vector<Point>& vertices,  std::vector<Point>& borders)
{
    setInstance(vertices, borders);
}

int MinimumSpanningTree::find( int i )
{
    if( subsets[i].parentId != i )
        subsets[i].parentId = find(subsets[i].parentId);
    
    return subsets[i].parentId;
}

void MinimumSpanningTree::Union(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);
    
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parentId = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parentId = xroot;
    
    else
    {
        subsets[yroot].parentId = xroot;
        subsets[xroot].rank++;
    }
}

void MinimumSpanningTree::CreateEdges()
{
    /* Complete Graph - n^2 edges */
    for( unsigned int i = 0; i < vertices.size(); i++ )
    {
        for( unsigned int j = 0; j < vertices.size(); j++ )
        {
            if( i == j )
                continue;
            
            if( vertices[i]->isBorder && vertices[j]->isBorder )
                continue;
            
            Edge e;
            e.p1 = vertices[i];
            e.p2 = vertices[j];
            e.cost = EuclideanDistance(e.p1->i, e.p1->j, e.p2->i, e.p2->j);
            edges.push_back(e);
        }
    }
    
    if( balanced || borders.empty() )
        return;
    
    /* Complete Graph - n^2 edges */
    for( unsigned int i = 0; i < vertices.size(); i++ )
    {
            Edge e;
            e.p1 = vertices[i];
            e.p2 = borders[i];
            e.cost = EuclideanDistance(e.p1->i, e.p1->j, e.p2->i, e.p2->j);
            edges.push_back(e);
    }

}

/* ----- Kruskall's Algorithm for Minimum Spanning Tree ----- */
double MinimumSpanningTree::ComputeMST( std::vector<Edge>& spanningTreeEdges )
{
    double cost = 0.0;
    spanningTreeEdges.clear();
    edges.clear();
    
    /* Creates all edges */
    CreateEdges();
    
    /* 1. Sorts the edge list */
    std::sort(edges.begin(), edges.end(), sortFunction);
    
    int nBorder = 0;
    int mst_size;
    
    if( balanced )
        mst_size = (int)vertices.size() - 1;
    else
        mst_size = (int)vertices.size();
    
    /* 2. Computes the MST  */
    for(unsigned int i = 0; i < edges.size(); i++)
    {
        if( edges[i].p1->isBorder || edges[i].p2->isBorder )
        {
            /* If the group of vertices is already balanced, don't compute the cost of any residue-to-border edge */
            if( balanced )
                continue;
            
            nBorder++;
            
            /* Only considers closest border point */
            if(nBorder > 1 )
                continue;
        }
        
        int i1, i2;
        i1 = edges[i].p1->group_n;
        i2 = edges[i].p2->group_n;
        
        int g1 = find(i1);
        int g2 = find(i2);
        
        if( g1 != g2 )
        {
            spanningTreeEdges.push_back(edges[i]);
            cost += edges[i].cost;
            
            Union( g1, g2 );
        }
        if( spanningTreeEdges.size() == mst_size )
            break;
    }

    edges.clear();
    return cost;
}
/* --- END --- */

double MinimumSpanningTree::ComputeCost()
{
    std::vector<Edge> sTe;
    return ComputeMST( sTe );
}

void MinimumSpanningTree::setInstance(std::vector<Point>& v,std::vector<Point>& b)
{
    vertices.clear();
    borders.clear();
    subsets.clear();
    
    int pos = 0, neg = 0;
    
    for( unsigned int i = 0; i < v.size(); i++ )
    {
        vertices.push_back(&v[i]);
        vertices[i]->group_n = i;
        
        Subset s;
        s.parentId = i;
        s.rank = 0;
        subsets.push_back(s);
        
        if( v[i].type == POS_RESIDUE )
            pos++;
        else if ( v[i].type == NEG_RESIDUE )
            neg++;
    }
    
    for( unsigned int i = 0; i < b.size(); i++ )
    {
        borders.push_back(&b[i]);
        borders[i]->group_n = (int)v.size() + i;
        Subset s;
        s.parentId = (int)v.size() + i;
        s.rank = 0;
        subsets.push_back(s);
    }
    
    if( pos == neg )
        balanced = true;
    else
        balanced = false;
}