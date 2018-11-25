#ifndef TPSORT_CPP
#define TPSORT_CPP

#include <iostream>

#include <vector>
#include <queue>
#include <algorithm>
#include <memory>
using namespace std;

#include "Vertex.h"
#include "Vertex.cpp"


vector<int> topSort(const vector<shared_ptr<Vertex> >& points)
{
    std::vector<shared_ptr<Vertex> > p = points;
    std::queue<shared_ptr<Vertex> > q;

    vector<int> tp_order;
    
    for (auto it = p.begin(); it != p.end(); ++it)
    {
        if ((*it)->indegree == 0)
            q.push(*it);
    }

    while (!q.empty()) {
        shared_ptr<Vertex>& v = q.front();
        q.pop();

        tp_order.push_back(v->name);
        

        for (auto it = v->adj.begin(); it != v->adj.end(); ++it)
        {
            if (--((*it)->indegree) == 0)
                q.push(*it);
        }
    }

    return tp_order;

}


#endif




    
    

    

        
        

        
    

    
    
        
        
            
        
    

    
    
    
        
    

    

