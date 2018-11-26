
/*******************************************
* Author: bravepam
* E-mail:1372120340@qq.com
* Blog:http://blog.csdn.net/zilingxiyue
*******************************************
*/

#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
#include<utility>
#include"FibonacciHeap.h"

//#define NOPARENT 0
#define MAX	0x7fffffff

using namespace std;
//enum color{ WHITE, GRAY, BLACK };

struct edgeNode
{//�߽ڵ�
	size_t adjvertex;//�ñߵĹ����Ķ���
	size_t weight;//��Ȩ��
	edgeNode *nextEdge;//��һ����
	edgeNode(size_t adj, size_t w) :adjvertex(adj), weight(w), nextEdge(nullptr){}
};

struct edge
{//�ߣ���edgeNode�б�
	size_t u, v;
	size_t weight;
	edge(size_t u_, size_t v_, size_t w) :u(u_), v(v_), weight(w){}
};


class AGraph
{//����ͼ
private:
	vector<edgeNode*> graph;
	size_t nodenum;
	void transformGraph(vector<edge>&);

	AGraph& operator=(const AGraph&);
	AGraph(const AGraph&);
public:
	AGraph(size_t n = 0){editGraph(n); }
	void editGraph(size_t n)
	{
		nodenum = n;
		graph.resize(n + 1);
	}
	size_t size()const { return nodenum; }
	void initGraph();//��ʼ������ͼ
	edgeNode* search(size_t, size_t);//���ұ�
	void add1Edge(size_t, size_t, size_t);
	void add2Edges(size_t, size_t, size_t);//��ӱ�
	void delete1Edge(size_t, size_t);
	void delete2Edges(size_t, size_t);//ɾ����
	size_t kruskal(AGraph*);
	size_t prim(AGraph*,size_t);
	void print();
	void destroy();
	~AGraph(){ destroy(); }
};

void AGraph::initGraph()
{
	size_t start, end;
	size_t w;
	ifstream infile("F:\\testdata\\mst.txt");
	while (infile >> start >> end >> w)
		add1Edge(start, end, w);
}

void AGraph::transformGraph(vector<edge> &E)
{
	for (size_t i = 1; i != graph.size(); ++i)
	{//����edgeNode�����edge
		edgeNode *curr = graph[i];
		while (curr != nullptr)
		{
			if (i < curr->adjvertex)
			{//����u,v֮��ı�ֻ�洢һ����(u,v)����u < v��
				edge e(i, curr->adjvertex, curr->weight);
				E.push_back(e);
			}
			curr = curr->nextEdge;
		}
	}
}

edgeNode* AGraph::search(size_t start, size_t end)
{
	edgeNode *curr = graph[start];
	while (curr != nullptr && curr->adjvertex != end)
		curr = curr->nextEdge;
	return curr;
}

void AGraph::add1Edge(size_t start, size_t end, size_t weight)
{
	edgeNode *curr = search(start, end);
	if (curr == nullptr)
	{
		edgeNode *p = new edgeNode(end, weight);
		p->nextEdge = graph[start];
		graph[start] = p;
	}
}

inline void AGraph::add2Edges(size_t start, size_t end, size_t weight)
{
	add1Edge(start, end, weight);
	add1Edge(end, start, weight);
}

void AGraph::delete1Edge(size_t start, size_t end)
{
	edgeNode *curr = search(start, end);
	if (curr != nullptr)
	{
		if (curr->adjvertex == end)
		{
			graph[start] = curr->nextEdge;
			delete curr;
		}
		else
		{
			edgeNode *pre = graph[start];
			while (pre->nextEdge->adjvertex != end)
				pre = pre->nextEdge;
			pre->nextEdge = curr->nextEdge;
			delete curr;
		}
	}
}

inline void AGraph::delete2Edges(size_t start, size_t end)
{
	delete1Edge(start, end);
	delete1Edge(end, start);
}

size_t AGraph::kruskal(AGraph *mst)
{//��³˹�����㷨����С��������������СȨֵ�ͣ���С��������¼��mst��
	struct findRoot:public binary_function<vector<size_t>,size_t,size_t>
	{//�ֲ����������࣬���ڲ�ѯ���鼯
		size_t operator()(vector<size_t> &UFS, size_t v)const
		{
			if (v == UFS[v]) return v;
			UFS[v] = findRoot()(UFS, UFS[v]);//·��ѹ��
			return UFS[v];
		}
	};
	struct edgeCompare:public binary_function<edge,edge,bool>
	{//�ֲ����������࣬���ڱ߱Ƚ���
		bool operator()(const edge &left, const edge &right)const
		{
			return left.weight < right.weight;
		}
	};
	vector<edge> E;
	transformGraph(E);//���ڽ�����ת��Ϊ�߼���
	vector<size_t> UFS(nodenum + 1);
	size_t sum = 0, cnt = 0;
	for (size_t i = 1; i <= nodenum; ++i)
		UFS[i] = i;//��ʼ�����鼯Union-Find-Set
	sort(E.begin(), E.end(), edgeCompare());//��edge�߰�Ȩֵ�ǵݼ�����
	for (size_t i = 0; i != E.size(); ++i)
	{//���������
		size_t u_root = findRoot()(UFS, E[i].u), v_root = findRoot()(UFS, E[i].v);
		if (u_root != v_root)
		{//�����ڲ�ͬ�����������ڵ㲻һ���������
			sum += E[i].weight;
			mst->add2Edges(E[i].u, E[i].v, E[i].weight);
			UFS[u_root] = v_root;
			++cnt;
		}
		if (cnt == nodenum - 1) break;//ѡ��n-1������
	}
	return sum;
}

size_t AGraph::prim(AGraph *mst,size_t u)
{//����ķ�㷨����С������������쳲������ѡ�������СȨֵ�ͣ�mst�洢��С��������ʱ��O(E+VlgV)
	vector<size_t> parent(nodenum + 1);
	//�洢ÿ��������쳲��������еĶ�Ӧ�ڵ�ĵ�ַ�����������޸ľ����
	vector<fibonacci_heap_node<size_t,size_t>*> V(nodenum + 1);
	fibonacci_heap<size_t, size_t> Q;//쳲������ѣ���Ϊ���룬ֵΪ������
	for (size_t i = 1; i <= nodenum; ++i)
	{
		parent[i] = i;
		if (i == u) V[i] = Q.insert(0, i);//����в���Ԫ�أ����ҽ��ڵ�����������
		else V[i] = Q.insert(MAX, i);
	}
	size_t sum = 0;
	while (!Q.empty())
	{
		pair<size_t, size_t> min = Q.extractMin();
		V[min.second] = nullptr;//�ÿգ���־�Ÿýڵ��Ѵ�ͼ��ɾ��
		sum += min.first;
		for (edgeNode *curr = graph[min.second]; curr; curr = curr->nextEdge)
		{//����Ϊ�н飬���¸��㵽MST�ľ���
			if (V[curr->adjvertex] != nullptr && curr->weight < V[curr->adjvertex]->key)
			{
				Q.decreaseKey(V[curr->adjvertex], curr->weight);
				parent[curr->adjvertex] = min.second;
			}
		}//���ñ߼���MST
		if (min.second != u) mst->add2Edges(parent[min.second], min.second,min.first);
	}
	return sum;
}

inline void AGraph::print()
{
	for (size_t i = 1; i != graph.size(); ++i)
	{
		edgeNode *curr = graph[i];
		cout << i;
		if (curr == nullptr) cout << " --> null";
		else
			while (curr != nullptr)
			{
				cout << " --<" << curr->weight << ">--> " << curr->adjvertex;
				curr = curr->nextEdge;
			}
		cout << endl;
	}
}

void AGraph::destroy()
{
	for (size_t i = 1; i != graph.size(); ++i)
	{
		edgeNode *curr = graph[i], *pre;
		while (curr != nullptr)
		{
			pre = curr;
			curr = curr->nextEdge;
			delete pre;
		}
		graph[i] = curr;
	}
}

const size_t nodenum = 9;

size_t main()
{
	AGraph graph(nodenum), mst(nodenum);
	graph.initGraph();
	graph.print();
	cout << endl;
	cout << graph.kruskal(&mst) << endl;
	mst.print();
	getchar();
	return 0;
}