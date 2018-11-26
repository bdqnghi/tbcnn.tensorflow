#include <iostream>
#include <vector>
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

// 图的深度优先遍历，基于递归实现，递归过程隐式的调用了栈

class DepthFirstSearch
{
public:
    DepthFirstSearch(Graph G, int s);

    bool hasPathTo(int v);
    stack<int> pathTo(int v);

private:
    int startS_;
    vector<bool> marked;
    vector<int> edgeTo;

    void dfs(Graph G, int s);
};

DepthFirstSearch::DepthFirstSearch(Graph G, int s)
{
    startS_ = s;
    marked = vector<bool>(G.V_Counts(), 0);
    edgeTo = vector<int>(G.V_Counts(),  0);

    dfs(G, s);
}

void DepthFirstSearch::dfs(Graph G, int s)
{
    marked.at(s) = 1;   // Visited
    for (auto w : G.Adjs(s))
    {
        if (!marked.at(w))
        {
            edgeTo.at(w) = s;
            dfs(G, w);      // 深度优先
        }
    }
}

bool DepthFirstSearch::hasPathTo(int v)
{
    return marked.at(v);
}

stack<int> DepthFirstSearch::pathTo(int v)
{
    stack<int> nodes;
    if (hasPathTo(v))
    {
        for (int x = 0; x != startS_; x = edgeTo.at(x))   // edgeTo是父连接
        {
            nodes.push(x);
        }

        return nodes;
    }
    else
        return stack<int>();   // no elements
}

int main() {
    //std::cout << "Hello, World!" << std::endl;

    return 0;
}
