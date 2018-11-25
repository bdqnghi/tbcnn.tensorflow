#pragma once
#include "Search.h"
#include "Queue.h"
class BreadthFirstSearch:public Search
{
public:
	BreadthFirstSearch(Graph& G, int s);
	bool Marked(int v) override;
	int Count() override;
private:
	void BFS(Graph& G, int s);
};

BreadthFirstSearch::BreadthFirstSearch(Graph& G, int s) :Search(G, s)
{
	BFS(G, s);
}

bool BreadthFirstSearch::Marked(int v)
{
	return m_bMarked[v];
}

int BreadthFirstSearch::Count()
{
	return m_nCount;
}

void BreadthFirstSearch::BFS(Graph& G, int s)
{
	Queue<int> q;
	q.Enqueue(s);
	while (!q.IsEmpty())
	{
		int nV = q.Dequeue();
		if(!m_bMarked[nV])
		{
			m_nCount++;
			m_bMarked[nV] = true;
			Bag<int> bagTemp = G.Adj(nV);
			for (int i = 0; i < bagTemp.Size(); i++)
			{
				if (!m_bMarked[bagTemp.Peek(i)])
				{
					q.Enqueue(bagTemp.Peek(i));
				}
			}
		}
	}
}