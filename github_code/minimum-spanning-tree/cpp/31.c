//
//  minimumSpanningTree.cpp
//  pathfinder
//
//  Created by Vince Mansel on 10/29/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include "minimumSpanningTree.h"

int CompareMinimumArcs(arcT *arc1, arcT *arc2) {
    double one = arc1->distance;
    double two = arc2->distance;
    if (one == two) return 0;
	if (one > two) return -1;
	return 1; // Minimum Distance
}

void PrintSet(nodeT *node) {
    cout << node->name << endl;
}

void minimumSpanningTree(Set<nodeT *> &graph, Map<nodeT *> &graphMap) {
    
    // R1: In Kruskal’s algorithm, you consider the arcs in the graph in order of increasing cost.
    PQueueT<arcT *> arcQueue1(CompareMinimumArcs);
    
    Map<Set<nodeT *> > nodeConnections;
    Map<nodeT *>::Iterator itr = graphMap.iterator();
    
    //R3: Since the goal is to minimize the overall total distance, it makes sense to consider shorter arcs before the longer ones.
    //    To process the arcs in order of increasing distance, the priority queue will come in handy again.
    
    //R4: This algorithm shall determine whether a given arc should be included.
    //The strategy to use is based on tracking connected sets.
    //For each node, maintain the set of the nodes that are connected to it.
    
    while (itr.hasNext()) {
        string nodeName = itr.next();
        Vector<arcT *> links = graphMap[nodeName]->links;
        
        //R5: At the start, each node is connected only to itself.
        nodeConnections[nodeName].add(links[0]->start);
        for (int i = 0; i < links.size(); i++) {
            arcQueue1.enqueue(links[i]);
        }
    }
    
    double total = 0; // Total distance or cost
    
    // R7: Continue considering arcs and merging connected sets until all nodes are joined into one set.
    
    cout << "Process edges in order of cost:" << endl;
    while (!arcQueue1.isEmpty()) {
        arcT *link = arcQueue1.dequeue();
        cout << link->distance << ": " << link->start->name << " -> " << link->end->name;
        
        //R6: When considering an arc, if its two endpoints already belong to the same connected set,
        //    there is no point in adding that arc and thus you skip it.
        
//        cout << endl;
//        cout << "Connections: " << link->start->name << endl;
//        nodeConnections[link->start->name].mapAll(PrintSet);
//        cout << endl;
//        cout << "Connections: " << link->end->name << endl;
//        nodeConnections[link->end->name].mapAll(PrintSet);
//        cout << endl;    
        
        Set<nodeT *> connectedSet = nodeConnections[link->start->name];
        connectedSet.intersect(nodeConnections[link->end->name]);
        
        // R2a: If the nodes at the endpoints of the arc are unconnected, then include this arc as part of the spanning tree.
        
        if (connectedSet.isEmpty()) {
            cout << endl;
//            cout << "           ***** Processed" << endl;
            DrawFilledCircleWithLabel(GetCoords(link->start), "Black", link->start->name);
            DrawFilledCircleWithLabel(GetCoords(link->end), "Black", link->end->name);
            DrawLineBetween(GetCoords(link->start), GetCoords(link->end), "Red");
            total += link->distance;
        }
        else {
            // R2b:If, however, the nodes are already connected by some path, discard this arc.
            cout << " (Not required)" << endl;
        }
        nodeConnections[link->start->name].unionWith(nodeConnections[link->end->name]);
        Set<nodeT *>::Iterator itr = nodeConnections[link->start->name].iterator();
        
        
        // Merge and update current connected members into one set while each member maintains a copy.
        
        while (itr.hasNext()) {
            nodeT * nextSet = itr.next();
            nodeConnections[nextSet->name].unionWith(nodeConnections[link->start->name]);
            nodeConnections[link->start->name].unionWith(nodeConnections[nextSet->name]);
        }
        
//        cout << "********************************************************************" << endl;
    }
    
    cout << "Total Distance = " << total << endl;
    
}


