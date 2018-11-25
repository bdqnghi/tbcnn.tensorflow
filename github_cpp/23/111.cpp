#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <fstream>
#include <string>
using namespace std;

struct node {
    int v;
    node *next;
    int c, f, cf;
    node (int j, node *t, int temp_c) {
        v = j; 
        next = t;
        c = temp_c;
        f = 0;
        cf = c - f;
    }
};
typedef node *linkSt;

void Print_list (linkSt);
void Print_residual_network (vector<linkSt>, int);
bool Find_adj_vertex (int, int, vector<linkSt>);
bool Augmenting_path (vector<linkSt>, int, int, int, int*);

void Print_list (linkSt head) {
    while (head != NULL) {
        cout << "link with: " << head->v << " c = " << head->c << " f = " << head->f << " cf = " << head->cf << "; ";
        head = head->next;
    }
    cout << "\n";
}

void Print_residual_network(vector<linkSt> adj, int v) {
    for (int i = 0; i < v; i++) {
        cout << i << ": "; 
        Print_list(adj[i]);
        cout << "\n";
    }
}

bool Find_adj_vertex(int i, int j, vector<linkSt> *adj) {
    linkSt vertex_view = (*adj)[j];
    
    while (vertex_view != NULL) {           
        if (vertex_view->v == i)
            return true;
        vertex_view = vertex_view->next;
    }
    
    return false;
}

bool Augmenting_path (vector<linkSt> adj, int v, int source, int sink, vector<int> *way) {
    
    queue<int> myqueue;
    vector<string> color;   
    vector<int> distance;   
    vector<int> min_way;    
    int u;
    
    for (int i = 0; i < v; i++) {
        color.push_back("White");
        distance.push_back(-1);
        min_way.push_back(-1);
    }
    color[source] = "Gray";
    distance[source] = 0;
    myqueue.push(source);
    
    
    
    while (!myqueue.empty()) {
        u = myqueue.front();
        myqueue.pop();
        for (linkSt t = adj[u]; t != NULL; t = t->next) {
            if ((color[t->v] == "White") && (t->cf > 0)) {
                color[t->v] = "Gray";
                distance[t->v] = distance[u] + 1;
                min_way[t->v] = u;
                myqueue.push(t->v);
            }
        }
        color[u] = "BLACK";
    }
    
    u = min_way[sink];
    way->push_back(sink);
    while (u != -1) {
        way->push_back(u);
        u = min_way[u];
    }
    int temp_swap;
    for (size_t i = 0; i < way->size() / 2; i++) {
        temp_swap = (*way)[i];
        (*way)[i] = (*way)[way->size() - i - 1];
        (*way)[way->size() - i - 1] = temp_swap;
    }
    
    if (distance[sink] != -1)
        return true;
    else
        return false;
}
    

int main() {
    const int MAXFLOW = 10000;
    ifstream File("GrafExKormen.txt");
    int j, i, c;
    int v;                      
    vector<linkSt> adj;         
    File >> v; 
    for (i = 0; i < v; i++)
        adj.push_back(NULL);    
    
    
    while (true) {
        File >> i >> j >> c;    
        if (i == -1)            
            break;
        adj[i] = new node (j, adj[i], c);
    }
    
    
    
    for (i = 0; i < v; i++) {               
        linkSt vertex_view = adj[i];        
        while (vertex_view != NULL) {       
            if (Find_adj_vertex(i, vertex_view->v, &adj) == false)              
                adj[vertex_view->v] = new node (i, adj[vertex_view->v], 0);     
            vertex_view = vertex_view->next;
        }
    }
    
    
    
    int source, sink;
    File >> source >> sink;
    
    
    vector<int> way;                        
    int cf_min = MAXFLOW;
    linkSt list_f = NULL, list_back = NULL; 
                                            
                                            
    int max_flow = 0;
    
    while (Augmenting_path(adj, v, source, sink, &way) == true) {
        cout << "way : ";
        for (size_t i = 0; i < way.size(); i++)
            cout << way[i] << "  ";
        printf("\n");
        
        
        for (size_t i = 0; i + 1 < way.size(); i++) {
            list_f= adj[way[i]];
            while (list_f != NULL) {
                if (list_f->v == way[i+1]) {
                    if (list_f->cf < cf_min)
                        cf_min = list_f->cf;
                    break;
                }
                list_f = list_f->next;
            }
        }
        
        printf("cf_min = %d\n\n", cf_min);
        max_flow += cf_min;
        list_f = NULL;
        list_back = NULL;
        for (size_t i = 0; i + 1 < way.size(); i++) {           
            list_f = adj[way[i]];
            while (list_f != NULL) {                            
                if (list_f->v == way[i+1]) {
                    list_f->f += cf_min;
                    list_f->cf = list_f->c - list_f->f;
                    
                    list_back = adj[way[i+1]];                  
                    
                    while (list_back != NULL) {                     
                        if (list_back->v == way[i]) {
                            list_back->f += (-1) * cf_min;
                            list_back->cf = list_back->c - list_back->f;
                            break;
                        }
                        list_back = list_back->next;
                    }
                    break;
                }
                list_f = list_f->next;
            }
        }
        
        Print_residual_network(adj, v);         
        printf("--------------------------------------------------------------------------------\n\n");
        way.clear();
        cf_min = MAXFLOW;
    }
    
    printf("RESULT: max fow = %d\n", max_flow);
    
    return 0;
}
