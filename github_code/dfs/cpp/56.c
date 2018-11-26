#include "DepthFirstSearch.h"

DepthFirstSearch::DepthFirstSearch(const Graph * g)
{
	this->g = g;
	this->graph_size = g->vertices.size();

	this->marks = vector<color>(graph_size);
	this->time_stamps = vector<TimeStamp>(graph_size);
	this->time_ordered_vlist = list<Vertex>(); 
}

DepthFirstSearch::~DepthFirstSearch()
{
	// Should delete g, but there are some problems
}

void DepthFirstSearch::search()
{
	time = 0;
	hasCycle = false;

	for (int i = 0; i < graph_size; i++) {
		marks.at(i) = WHITE;
	}

	for (int i = 0; i < graph_size; i++) {
		if (marks.at(i) == WHITE) {
			visit(i);	
		}
	}
}

vector<int> DepthFirstSearch::getFinishedTimes() const
{
	vector<int> ft = vector<int>(graph_size);

	for (int i = 0; i < graph_size; i++)
		ft.push_back(time_stamps[i].finished_time);

	return ft;
}


vector<int> DepthFirstSearch::getDiscoveredTimes() const
{
	vector<int> dt = vector<int>(graph_size);

	for (int i = 0; i < graph_size; i++)
		dt.push_back(time_stamps[i].discovered_time);

	return dt;
}

bool DepthFirstSearch::isCiclyc() const
{
	return hasCycle;
}

list<Vertex> DepthFirstSearch::getVerticesOrderedByFTime() const
{
	return time_ordered_vlist;
}

void DepthFirstSearch::visit(int v)
{
	time = time + 1;

	marks[v] = GRAY;
	time_stamps[v].discovered_time = time;

	vector<Edge> adj = g->vertices.at(v).adjacencyList;

	for (unsigned int i = 0; i < adj.size(); i++) {
		int next_vertex = g->index_table.at(adj[i].v.id);
		if (marks[next_vertex] == WHITE)
			visit(next_vertex);
		else if (marks[next_vertex] == GRAY)
			hasCycle = true;
	}

	time = time + 1;

	marks[v] = BLACK;
	time_stamps[v].finished_time = time;
	time_ordered_vlist.push_front(g->vertices[v]);
}

vector<list<Vertex>> DepthFirstSearch::specialSearch(list<Vertex> orderedList)
{
	// each strongly connected componnent will be here
	vector<list<Vertex>> forest;

	for (int i = 0; i < graph_size; i++) {
		marks.at(i) = WHITE;
	}

	list<Vertex>::iterator it;
	for (it = orderedList.begin(); it != orderedList.end(); it++) {
		int i = g->index_table.at(it->id);
		if (marks.at(i) == WHITE) {
			list<Vertex> tree;
			tree.push_back(*it);
			specialVisit(i, tree);
			forest.push_back(tree);
		}
	}

	return forest;
}

void DepthFirstSearch::specialVisit(int v, list<Vertex>& l)
{
	marks[v] = GRAY;

	vector<Edge> adj = g->vertices[v].adjacencyList;

	for (unsigned int i = 0; i < adj.size(); i++) {
		int next_vertex = g->index_table.at(adj[i].v.id);
		if (marks[next_vertex] == WHITE) {
			l.push_back(g->vertices[next_vertex]);
			specialVisit(next_vertex, l);
		}
	}

	marks[v] = BLACK;
}

