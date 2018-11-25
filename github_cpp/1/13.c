







#ifndef GTL_BFS_H
#define GTL_BFS_H

#include <GTL/GTL.h>
#include <GTL/algorithm.h>
#include <GTL/node_map.h>

#include <deque>

__GTL_BEGIN_NAMESPACE


class GTL_EXTERN bfs : public algorithm
{
public:
    
    
    bfs ();

    
    virtual ~bfs ();

    int run (graph& G);

    
    virtual int check (graph& ) { return GTL_OK; }

    virtual void reset ();
    
    
    
    

    
    void start_node (const node& n) {start = n;}

    
    node start_node () const {return start;}

    
    void scan_whole_graph (bool set) {whole_graph = set;}
    
    
    bool scan_whole_graph () const {return whole_graph;}

    
    void calc_level (bool set);
    
    
    bool calc_level () const {return level_number != 0;}

    
    void store_non_tree_edges (bool set);

    
    bool store_non_tree_edges () const {return non_tree != 0;}


    
    void store_preds (bool set);

    
    bool store_preds () const {return preds != 0;}

    
    bool reached (const node& n) const
	{return bfs_number[n] != 0;}

    
    int bfs_num (const node& n) const 
	{return bfs_number[n];}

    
    int operator[] (const node& n) const 
	{return bfs_number[n];}

    
    int level (const node& n) const
	{assert (level_number); return (*level_number)[n];}

    
    node father (const node& n) const
	{assert (preds); return (*preds)[n];}

    
	typedef edges_t::const_iterator tree_edges_iterator;

    
    tree_edges_iterator tree_edges_begin () const 
	{return tree.begin();}

    
    tree_edges_iterator tree_edges_end () const
	{return tree.end();}
   
    
	typedef nodes_t::const_iterator bfs_iterator;

    
    bfs_iterator begin () const 
	{return bfs_order.begin();}

    
    bfs_iterator end () const 
	{return bfs_order.end();}

    
	typedef edges_t::const_iterator non_tree_edges_iterator;

    
    non_tree_edges_iterator non_tree_edges_begin () const 
	{assert (non_tree);  return non_tree->begin(); }

    
    non_tree_edges_iterator non_tree_edges_end () const 
	{assert (non_tree); return non_tree->end(); }
    
    
	typedef std::list<bfs_iterator>::const_iterator roots_iterator;

    
    roots_iterator roots_begin () const 
	{return roots.begin();}

    
    roots_iterator roots_end () const 
	{return roots.end();}

    
    int number_of_reached_nodes () const
	{return reached_nodes;}

    
    
    

    
    virtual void init_handler (graph& ) { };

    
    virtual void end_handler (graph& ) { };

    
    virtual void popped_node_handler (graph& , node& ) { };

    
    virtual void finished_node_handler (graph& , node& ) { };

    
    virtual void unused_node_handler (graph& , node& , node& ) { };

    
    virtual void used_node_handler (graph& , node& , node& ) { };

    
    virtual void new_start_handler (graph& , node& ) { };

private:

    void bfs_sub (graph&, const node&, edge_map<int>*);

protected:

    
    
    
    
    
    int act_bfs_num;

    
	std::deque<node> qu;

    
	nodes_t bfs_order;

    
	edges_t tree;

    
    node_map<int> bfs_number;

    
    int reached_nodes;
    
    
	std::list<bfs_iterator> roots;

    
    
    

    
    bool whole_graph;

    
    node start;

    
    node_map<int>* level_number;

    
	edges_t* non_tree;

    
    node_map<node>* preds;
};

__GTL_END_NAMESPACE

#endif 




