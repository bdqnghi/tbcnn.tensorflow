#ifndef TPSORT_CPP
#define TPSORT_CPP

#include <iostream>
// #include <list>
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
        // cout << v->name << " ";

        for (auto it = v->adj.begin(); it != v->adj.end(); ++it)
        {
            if (--((*it)->indegree) == 0)
                q.push(*it);
        }
    }

    return tp_order;

}


#endif


// int main()
// {
    // vector<shared_ptr<Vertex> > points;
    // int from, to;

    // while (cin >> from >> to) {

        // shared_ptr<Vertex> p1 { new Vertex { from } };
        // shared_ptr<Vertex> p2 { new Vertex { to } };

        // readEdges(points, p1, p2);
    // }

    // for (auto it = points.begin(); it != points.end(); ++it)
    // {
        // cout << (*it)->name << " " << (*it)->indegree <<  ": ";
        // for (auto it2 = (*it)->adj.begin(); it2 != (*it)->adj.end(); ++it2)
            // cout << (*it2)->name << " ";
        // cout << endl;
    // }

    // vector<int> tp_order = topSort(points);
    // cout << "topological sort: ";
    // for (int i = 0; i < tp_order.size(); ++i)
        // cout << tp_order[i] << " ";
    // cout << endl;

    // return 0;
// }
