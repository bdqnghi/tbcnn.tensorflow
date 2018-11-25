

#include<iostream>
#include<vector>
#include<cfloat>
#include<queue>
#include<cmath>
#include<fstream>
#include<cassert>
#include<algorithm>

#include "FlowNetwork.cpp"
#include "FlowEdge.cpp"

using namespace std;


class FordFulkerson {
    const double FLOATING_POINT_EPSILON = 1E-11;
    
    bool *marked;               
    FlowEdge *edgeTo;           
    double value;               
    
    
    double excess(FlowNetwork G, int v) {
        double excess = 0.0;
        for (FlowEdge e : G.getadj(v)) {
            if (v == e.from()) excess -= e.getFlow();
            else               excess += e.getFlow();
        }
        return excess;
    }
    
    
    bool check(FlowNetwork G, int s, int t) {
        
        
        if (!isFeasible(G, s, t)) {
            cerr << "Flow is infeasible" << endl;
            return false;
        }
        
        
        if (!inCut(s)) {
            cerr << "source " << s << " is not on source side of min cut" << endl;
            return false;
        }
        if (inCut(t)) {
            cerr << "sink " << t << " is on source side of min cut" << endl;
            return false;
        }
        
        
        double mincutValue = 0.0;
        for (int v = 0; v < G.getV(); v++) {
            for (FlowEdge e : G.getadj(v)) {
                if ((v == e.from()) && inCut(e.from()) && !inCut(e.to()))
                    mincutValue += e.getCapacity();
            }
        }
        
        if (abs(mincutValue - value) > FLOATING_POINT_EPSILON) {
            cerr << "Max flow value = " << value << ", min cut value = " << mincutValue << endl;
            return false;
        }
        
        return true;
    }
    
    
    bool isFeasible(FlowNetwork G, int s, int t) {
        
        
        for (int v = 0; v < G.getV(); v++) {
            for (FlowEdge e : G.getadj(v)) {
                if (e.getFlow() < -FLOATING_POINT_EPSILON || e.getFlow() > e.getCapacity() + FLOATING_POINT_EPSILON) {
                    cerr << "Edge does not satisfy capacity constraints: " << e << endl;
                    return false;
                }
            }
        }
        
        
        if (abs(value + excess(G, s)) > FLOATING_POINT_EPSILON) {
            cerr << "Excess at source = " << excess(G, s) << endl;
            cerr << "Max flow         = " << value << endl;
            return false;
        }
        if (abs(value - excess(G, t)) > FLOATING_POINT_EPSILON) {
            cerr << "Excess at sink   = " << excess(G, t) << endl;
            cerr << "Max flow         = " << value << endl;
            return false;
        }
        for (int v = 0; v < G.getV(); v++) {
            if (v == s || v == t) continue;
            else if (abs(excess(G, v)) > FLOATING_POINT_EPSILON) {
                cerr << "Net flow out of " << v << " doesn't equal zero" << endl;
                return false;
            }
        }
        return true;
    }
    
    
    
    
    
    bool hasAugmentingPath(FlowNetwork G, int s, int t) {
        if(edgeTo != nullptr) delete edgeTo;
        if(marked != nullptr) delete marked;
        edgeTo = new FlowEdge[G.getV()];
        marked = new bool[G.getV()];
        fill(marked, marked+G.getV(), false);
        
        
        queue<int> myqueue;
        myqueue.push(s);
        marked[s] = true;
        while (!myqueue.empty() && !marked[t]) {
            int v = myqueue.front();
            myqueue.pop();
            
            for (FlowEdge e : G.getadj(v)) {
                int w = e.other(v);
                
                
                if (e.residualCapacityTo(w) > 0) {
                    if (!marked[w]) {
                        edgeTo[w] = e;
                        marked[w] = true;
                        myqueue.push(w);
                    }
                }
            }
        }
        
        return marked[t];
    }


    
public:
    
    FordFulkerson(FlowNetwork G, int s, int t) {
        
        
        value = excess(G, t);
        while (hasAugmentingPath(G, s, t)) {
            
            double bottle = DBL_MAX;
            for (int v = t; v != s; v = edgeTo[v].other(v)) {
                bottle = min(bottle, edgeTo[v].residualCapacityTo(v));
            }
            
            for (int v = t; v != s; v = edgeTo[v].other(v)) {
                G.addResidualFlowTo(edgeTo[v], v, bottle);
            }
            
            value += bottle;
        }
        
        
        
    }
    
    double getvalue()  {
        return value;
    }
    
    bool inCut(int v)  {
        return marked[v];
    }
    
};

int main() {
    
    
    int V = 6;
    int E = 10;
    int s = 0, t = V-1;
    ifstream in("input.txt");
    FlowNetwork G (in);
    
    
    FordFulkerson maxflow(G, s, t);
    cout << "Max flow from " << s << " to " << t << endl;
    for (int v = 0; v < G.getV(); v++) {
        for (FlowEdge e : G.getadj(v)) {
            if ((v == e.from()) && e.getFlow() > 0)
                cout << "   " << e << endl;
        }
    }
    
    
    
    cout << "Min cut: " << endl;
    for (int v = 0; v < G.getV(); v++) {
        if (maxflow.inCut(v)) cout << v << " ";
    }
    cout << endl;
    
    cout << "Max flow value = " << maxflow.getvalue() << endl;
}