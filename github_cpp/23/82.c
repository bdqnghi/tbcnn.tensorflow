#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "queue.cpp"
#include "flowNetwork.cpp"
using namespace std;

int min(int a, int b)
{
    if(a<b)
        return a;
    return b;
}

class FordFulkerson
{
    private:
        bool* marked;
        FlowEdge<int>** edgeTo;
        int value;
    public:
        FordFulkerson(FlowNetwork G, int s, int t)
        {
            value = 0;
            while(hasAugmentingPath(G, s, t))
            {
                int bottle = INT_MAX;
                for(int a = t; a!=s; a = edgeTo[a]->other(a))
                    bottle = min(bottle, edgeTo[a]->residualCapacityTo(a));
                for(int a = t; a!=s; a = edgeTo[a]->other(a))
                    edgeTo[a]->addResidualFlowTo(a, bottle);
                value += bottle;
            }
        }
        int getValue(){return value;}

        bool hasAugmentingPath(FlowNetwork G, int s, int t)
        {
            edgeTo = new FlowEdge<int>*[G.getV()];
            marked = new bool[G.getV()];

            for(int i=0; i<G.getV(); i++)
                marked[i] = false;

            Queue<int> q;
            q.enqueue(s);
            marked[s] = true;
            int p;

            while(q.getSize() != 0)
            {
                int v = q.dequeue();
                
                
                for(List<int>::iterator it=G.getAdj(v).begin(); it!=NULL; ++it)
                {
                    int w = (*it)->other(v);
                    if((*it)->residualCapacityTo(w) > 0 && !marked[w])
                    {
                        edgeTo[w] = (*it);
                        marked[w] = true;
                        q.enqueue(w);
                    }
                }
                
            }
            return marked[t];
        }
};

int main()
{
    int i,j,k,u,v,w,t;

    cin >> i;
    FlowNetwork G(i);

    cin >> u >> v >> t;
    while(u!=-1)
    {
        G.addEdge(u,v,t);
        cin >> u >> v >> t;
    }
    G.displayFlowNetwork();

    cout << endl << endl;
    cin >> i >> j;

    FordFulkerson FF(G, i, j);
    cout << FF.getValue() << endl;
}
