







#include "minimumSpanningTree.h"

int CompareMinimumArcs(arcT *arc1, arcT *arc2) {
    double one = arc1->distance;
    double two = arc2->distance;
    if (one == two) return 0;
	if (one > two) return -1;
	return 1; 
}

void PrintSet(nodeT *node) {
    cout << node->name << endl;
}

void minimumSpanningTree(Set<nodeT *> &graph, Map<nodeT *> &graphMap) {
    
    
    PQueueT<arcT *> arcQueue1(CompareMinimumArcs);
    
    Map<Set<nodeT *> > nodeConnections;
    Map<nodeT *>::Iterator itr = graphMap.iterator();
    
    
    
    
    
    
    
    
    while (itr.hasNext()) {
        string nodeName = itr.next();
        Vector<arcT *> links = graphMap[nodeName]->links;
        
        
        nodeConnections[nodeName].add(links[0]->start);
        for (int i = 0; i < links.size(); i++) {
            arcQueue1.enqueue(links[i]);
        }
    }
    
    double total = 0; 
    
    
    
    cout << "Process edges in order of cost:" << endl;
    while (!arcQueue1.isEmpty()) {
        arcT *link = arcQueue1.dequeue();
        cout << link->distance << ": " << link->start->name << " -> " << link->end->name;
        
        
        
        







        
        Set<nodeT *> connectedSet = nodeConnections[link->start->name];
        connectedSet.intersect(nodeConnections[link->end->name]);
        
        
        
        if (connectedSet.isEmpty()) {
            cout << endl;

            DrawFilledCircleWithLabel(GetCoords(link->start), "Black", link->start->name);
            DrawFilledCircleWithLabel(GetCoords(link->end), "Black", link->end->name);
            DrawLineBetween(GetCoords(link->start), GetCoords(link->end), "Red");
            total += link->distance;
        }
        else {
            
            cout << " (Not required)" << endl;
        }
        nodeConnections[link->start->name].unionWith(nodeConnections[link->end->name]);
        Set<nodeT *>::Iterator itr = nodeConnections[link->start->name].iterator();
        
        
        
        
        while (itr.hasNext()) {
            nodeT * nextSet = itr.next();
            nodeConnections[nextSet->name].unionWith(nodeConnections[link->start->name]);
            nodeConnections[link->start->name].unionWith(nodeConnections[nextSet->name]);
        }
        

    }
    
    cout << "Total Distance = " << total << endl;
    
}


