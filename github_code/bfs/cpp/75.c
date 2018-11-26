//
// Created by smher on 18-7-28.
//

/*!
 * 广度优先，基于队列实现
 */

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

template <typename T>
class Bag
{
public:
    class Node
    {
    public:
        Node(T ele):item(ele){}
        T item;
        Node * next = nullptr;
    };

    void add(T ele);
    Node * begin()
    {
        return first;
    }

    Node* end()
    {
        return first + N;
    }

private:
    Node* first = nullptr;
    int N = 0;
};

template <typename T>
void Bag<T>::add(T ele)
{
    Node* oldfirst = first;
    first = new Node(ele);
    first->next = oldfirst;
    N++;
}

//template <typename T>
class Graph
{
public:
    typedef Bag<int>* BagPtr;
    Graph(int v)
    {
        V = v;   // the number of vertexes
        E = 0;
        adj = new BagPtr [v];
        for(int i = 0; i < v; ++i)
            adj[i] = new Bag<int>();
    }
    ~Graph()
    {
    }

    int V_Counts()
    {
        return V;
    }

    int E_Counts()
    {
        return E;
    }
    vector<int> Adjs(int s);

private:
    int V = 0;   // number of vertexes
    int E = 0;   // number of edges
    BagPtr* adj = nullptr;
};

vector<int> Graph::Adjs(int s)          // TODO: to be implemented
{
    vector<int> a;
    return a;
}

class BreadthFirstSearch
{
public:
    BreadthFirstSearch(Graph G, int s);

    bool hasPathTo(int v);
    stack<int> pathTo(int v);
private:
    int startS_;
    vector<bool> marked;
    <int> edgeTo;

    void bfs(Graph G, int s);
};

BreadthFirstSearch::BreadthFirstSearch(Graph G, int s)
{
    startS_ = s;
    marked = vector<bool>(G.V_Counts(), 0);
    edgeTo = vector<bool>(G.V_Counts(), 0);

    bfs(G, s);
}

void BreadthFirstSearch::bfs(Graph G, int s)
{
    marked.at(s) = 1;
    eles = queue<int>;
    eles.push(s);
    while(!eles.empty())
    {
        v = eles.front();
        eles.pop();
        for (auto w : G.Adjs(v))
        {
            if (!marked.at(w))
            {
                edgeTo.at(w) = v;
                marked.at(w) = 1;
                eles.push(w);
            }
        }
    }
}

bool BreadthFirstSearch::hasPathTo(int v)
{
    return marked.at(v);
}

stack<int> BreadthFirstSearch::pathTo(int v) 
{
    stack<int> eles;
    if (marked.at(v))
    {
        for (int x = 0; x != startS_ ; x=edgeTo.at(x))
        {
            eles.push(x);
        }
        return eles;
    }
    else
        return stack<int>();
}



