#include "Kruskal.h"
#include <list>
#include <set>
#include <map>
#include <cassert>

using namespace std;

/* Insert and edge between 'a' and 'b' */
void Graph :: insert_weighted_edge (int from_a, int to_b, int w) {
  
  map<int,  set<int> > :: iterator from_temp_a,  to_temp_b;

    from_temp_a = data.find(from_a);
    to_temp_b   = data.find(to_b  );

    if(from_temp_a == data.end() ) {
        set<int> temp_set;
        temp_set.insert(to_b);
        pair<int,  set<int> > temp_pair(from_a, temp_set);
        data.insert(temp_pair);
    }
    else if(from_temp_a != data.end() ) {
        from_temp_a->second.insert(to_b);
    }
    else {
        cerr<<"\nWTF !"<<endl;
    }

    if(to_temp_b == data.end()) {
        set<int> temp_set;
        temp_set.clear();
        temp_set.insert(from_a);
        pair<int, set<int> > temp_pair1(to_b, temp_set);
        data.insert(temp_pair1);
    }
    else if(to_temp_b != data.end() ) {
        to_temp_b->second.insert(from_a);
    }
    else {
        cerr<<"\nWTF !"<<endl;
    }
    
    /* Setting the weights to the edges */
    set_weight(from_a,  to_b, w);
    set_weight(to_b,  from_a, w);
}

/* Check if edge from 'a' to 'b' exists in the graph */
bool Graph :: is_edge (int from_v, int to_v) {
    map<int,  set<int> > :: iterator map_itr = find_vertex(from_v);
    
    if (map_itr ==  data.end() ) return false;
    return (map_itr->second.find(to_v) !=  map_itr->second.end());
}

/* Check if vertex 'v' exists */
map<int,  set<int> > :: iterator Graph :: find_vertex(int v) {
    return data.find(v);
}

/* Delete a vertex in the graph */
void Graph :: delete_vertex(int v) {
    multimap<int, set<int>, int> :: iterator temp_iter = data.find(v);

    if(temp_iter == data.end()) {
        cerr<<"\nEdge not found"<<endl;
    }
    else {
        multimap<int, set<int>, int> :: iterator i;

        for(i = data.begin(); i != data.end(); i++) {
            i->second.erase(v);
        }
        data.erase(temp_iter);
    }
}

/* Delte an edge in the graph */
void Graph :: delete_edge(int from_a, int to_b) {
    multimap<int, set<int>, int> :: iterator x, y;

    x = data.find(from_a);
    y = data.find(to_b  );

    if(x != data.end() && y != data.end()) {
        x->second.erase(to_b  );
        y->second.erase(from_a);
    }
    else {
        cerr<<"\nEdge not present"<<endl;
    }

}

/* Find the Minimum Spanning Tree using Kruskal's Algorithm */
void Graph :: MST_using_KRUSKAL(vector<pair<int, int> > &mst_tree_edges){
	list < set<int> > 			forest; 
	set < int >				temp_set; 
	map < int, set<int> >::iterator 	map_itr; 

	/* Populate forest. Each vertex is separte tree. */
	for(map_itr = data.begin(); map_itr != data.end(); map_itr ++){
		temp_set.insert(map_itr->first); 
		forest.push_back(temp_set); 
		temp_set.clear(); 
	}
	
	/* Sorting based on weight. 
	 * Create a map with weight as the key and the edge as the value. 
	 */
	multimap<int, pair<int, int> >					temp_edge_weights; 
	map<pair<int, int>, int>::iterator				w_itr; 
	typedef multimap<int, pair<int, int> >::iterator			mm_itr; 

	/* For each edge in the graph. */
	for(w_itr = edge_weights.begin(); w_itr != edge_weights.end(); w_itr++){
	  /* Find the list of edges with this weight. */
	  pair<mm_itr, mm_itr> mm_itr_pair = temp_edge_weights.equal_range(w_itr->second); 

	  /* Make sure the find is successful. */
	  if(mm_itr_pair.first != mm_itr_pair.second){
	    cout << "Weight found: " << w_itr->second << endl;

	    /* Traverse each edge with this weight. */
	    bool found_flag = false; 
	    for(mm_itr mm_itr_1 = mm_itr_pair.first; mm_itr_1 != mm_itr_pair.second; mm_itr_1 ++){
		cout << "Comparing: " << mm_itr_1->second.first  << ", " << w_itr->first.second << endl; 
		cout << "Comparing: " << mm_itr_1->second.second << ", " << w_itr->first.first  << endl; 

		if((mm_itr_1->second.first == w_itr->first.second) && (mm_itr_1->second.second == w_itr->first.first)){
		    found_flag = true; 
		    break; 
		}
	    }
				
	    /* Check if found. */
	    if(found_flag == false){
	      /* None of the edge matched. */
	      cout << "inserting " << w_itr->second << ", " << w_itr->first.first << ", " << w_itr->first.second << endl; 
	      temp_edge_weights.insert(pair<int, pair<int, int> >(w_itr->second, w_itr->first)); 
	    }
	    else{
		/* One of the edge matched. */
		cout << "Edge " << w_itr->first.first << ", " << w_itr->first.second << " need not be inserted" << endl; 
	    }
	  }
	  else{
		/* Find is unsuccessful. */
		cout << "Weight not found: " << w_itr->second << endl;
		cout << "inserting " << w_itr->second << ", " << w_itr->first.first << ", " << w_itr->first.second << endl; 
		
		/* Insert the new edge. */
		temp_edge_weights.insert(pair<int, pair<int, int> >(w_itr->second, w_itr->first)); 
	  }	
	}
	
	/* Printing the sorted list. */
	multimap<int, pair<int, int> >::iterator w_temp_itr; 
		cout << "Sorted list of edges: " << endl; 
		for(w_temp_itr = temp_edge_weights.begin(); w_temp_itr != temp_edge_weights.end(); w_temp_itr ++){
			cout << w_temp_itr->second.first << "->" << w_temp_itr->second.second << ": " << w_temp_itr->first << endl; 
		}

	/* Printing forest. */
	cout << "Current forest: " << endl; 
	for(list<set<int> >::iterator f_itr = forest.begin(); f_itr != forest.end(); f_itr ++){
	  if(! f_itr->empty()){
	    cout << "{"; 
	    for(set<int>::iterator set_int_itr = f_itr->begin(); set_int_itr != f_itr->end(); set_int_itr ++){
	      cout << *set_int_itr << " "; 
	    }
	    cout << "} " << endl; 
	  }
	}
	

	/* For each edge in increasing order of weight. */
	for(w_temp_itr = temp_edge_weights.begin(); w_temp_itr != temp_edge_weights.end(); w_temp_itr ++){
	    cout << "Testing edge " << w_temp_itr->second.first << " -> " << w_temp_itr->second.second; 
	    cout << " (" << w_temp_itr->first << ")" << endl; 
	    
	    cout << "Checking whether in same set: " << w_temp_itr->second.first << ", " << w_temp_itr->second.second << endl; 
	    list<set<int> >::iterator itr_1, itr_2; 
	    set<int>  ::iterator itr_3, itr_4; 
	    bool found_flag = false; 

	    /* Find the set of the first element. */
	    found_flag = false; 
	    for(itr_1 = forest.begin(); itr_1 != forest.end(); itr_1 ++){
		itr_3 = itr_1->find(w_temp_itr->second.first); 
		if(itr_3 != itr_1->end()){ found_flag = true; break; }
	    }
	    assert(found_flag == true); 

	    /* Find the set of the second element. */
	    for(itr_2 = forest.begin(); itr_2 != forest.end(); itr_2 ++){
		itr_4 = itr_2->find(w_temp_itr->second.second); 
		if(itr_4 != itr_2->end()){ found_flag = true; break; }
	    }
	    assert(found_flag == true); 

		
	    /* See if they are in the same set or not. */
	    if(itr_1 != itr_2){
	      /* They are in different trees. */
	      cout << "They are in different trees. " << endl; 

	      /* Add them to the set of edges in the MST. */
	      cout << "Adding the edges " << *itr_3 << ", " << *itr_4 << " to the MST. " << endl; 
	      mst_tree_edges.push_back(pair<int, int>(*itr_3, *itr_4)); 

	      /* Combine them into a single tree (set). */
	      for(set<int>::iterator itr_5 = itr_2->begin(); itr_5 != itr_2->end(); itr_5++){
		itr_1->insert(*itr_5); 
	      }
	      itr_2->clear(); 
			
	    }
	    else{
		cout << "They are in the same tree. So cannot be added" << endl; 
	    }

	for(vector<pair<int, int> >::iterator te_itr = mst_tree_edges.begin(); te_itr != mst_tree_edges.end(); te_itr ++){
		cout << te_itr->first << ", " << te_itr->second << endl; 
	}

	/* If all the edges are added, you can stop. 
	 * For a graph with n vertices, its MST will contain (n-1) edges. 
	 */
	if(mst_tree_edges.size() == vertex_count() - 1){
	  cout << "All the edges have been added. " << endl; 
	  break; 
	}

	/* Printing forest. */
	cout << "Current forest: " << endl; 
	for(list<set<int> >::iterator f_itr = forest.begin(); f_itr != forest.end(); f_itr ++){
	  if(! f_itr->empty()){
	    cout << "{"; 
	    for(set<int>::iterator set_int_itr = f_itr->begin(); set_int_itr != f_itr->end(); set_int_itr ++){
	      cout << *set_int_itr << " "; 
	    }
	    cout << "} " << endl; 
	  }
	}
      }
	
      return; 
}

/* Get the weight of an edge of the graph */	
int Graph :: get_weight(int from_v,  int to_v) {
  
  if (is_edge(from_v,  to_v)) {
    pair<int,  int> wt_pair(from_v,  to_v);
    return edge_weights.find(wt_pair)->second;
  }
  else {
    cerr << "\nEdge not found" << endl;
    return -1;
  }
} 

/* Set the weight of an edge of a graph */
void Graph :: set_weight(int from_v,  int to_v,  int weight) {
  
  if (is_edge(from_v,  to_v)) {
    pair<int,  int> weight_pair(from_v,  to_v);
    edge_weights[weight_pair] = weight;
  }
  else {
    cerr << "\nNo edge found" << endl;
    return;
  }
}

/* Print the contents of the graph */
void Graph :: print(void ) {
    map< int,  set<int> > :: iterator iter;

    for(iter = data.begin(); iter != data.end(); iter++) {
        cout<<iter->first;
        for(set<int> :: iterator i = iter->second.begin(); i != iter->second.end(); i++ ) {
            cout<<" --> "<<*i;
        }
        cout<<";"<<endl;
    }

}