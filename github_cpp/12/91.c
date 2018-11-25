




























#include "general_head.h"
#include "graph.h"

extern void kruskal(edge_list& e);
int tree_weight(edge_list e);
void bfs_visit(edge_list e, int **max_edge, int n, int beg);

int second_minimum_spanning_tree(edge_list e, int n)
{
 
	kruskal(e);
	int weight = tree_weight(e);
	
	
	int **max_edge = new int*[MAX];
	for(int i = 0; i < MAX; ++ i){
		max_edge[i] = new int[MAX];
		memset(max_edge[i], 0, MAX * sizeof(int));
	}
	
	for(int i = 0; i < n; ++ i)
		bfs_visit(e, max_edge, n, i);
	
	int min_weight(INF);
	for(int i = 0; i < (int)e.e_l.size(); ++ i)
		if(!e.e_l[i].e_join)
			
			
			
			min_weight = min(min_weight,
					weight + (int)e.e_l[i].e_value -
					max_edge[e.e_l[i].e_beg][e.e_l[i].e_end]);
	return(min_weight);
}
int tree_weight(edge_list e)
{
	int weight(0);
	for(int i = 0; i < (int)e.e_l.size(); ++ i)
		if(e.e_l[i].e_join)
			weight += e.e_l[i].e_value;
	return(weight);
}
void bfs_visit(edge_list e, int **max_edge, int n, int beg)
{
	
	
	int visit_node[MAX], visit_edge[MAX];
	memset(visit_node, 0, MAX * sizeof(int));
	memset(visit_edge, 0, MAX * sizeof(int));
	
	queue<int> q;
	q.push(beg);
	visit_node[beg] = 1;
	
	while(!q.empty()){
		int p = q.front(); q.pop();
		
		for(int i = 0; i < (int)e.e_l.size(); ++ i){
			if(e.e_l[i].e_join and !visit_edge[i] and
					(e.e_l[i].e_beg == p or e.e_l[i].e_end == p)){
				
				
				if(e.e_l[i].e_beg == p){
					
					if(max_edge[beg][e.e_l[i].e_end] <
							e.e_l[i].e_value){
						max_edge[beg][e.e_l[i].e_end] = e.e_l[i].e_value;
						max_edge[e.e_l[i].e_end][beg] = e.e_l[i].e_value;
					}
					
					q.push(e.e_l[i].e_end);
					visit_node[e.e_l[i].e_end] = 1;
				}
				if(e.e_l[i].e_end == p){
					
					if(max_edge[beg][e.e_l[i].e_beg] <
							e.e_l[i].e_value){
						max_edge[beg][e.e_l[i].e_beg] = e.e_l[i].e_value;
						max_edge[e.e_l[i].e_beg][beg] = e.e_l[i].e_value;
					}
					q.push(e.e_l[i].e_beg);
					visit_node[e.e_l[i].e_beg] = 1;
				}
				
				visit_edge[i] = 1;
			}
		}
	}
}
