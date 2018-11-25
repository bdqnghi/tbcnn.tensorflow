

#ifndef DEPTH_H
#define DEPTH_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <assert.h>
#include <cmath>
#include "grid.h"
#include "tree.h"

using namespace std;

class depth{
public:
    void set_coords(double x, double y, grid* gp);
    void run_depth_first(grid* gp, tree* tp);
    void reset_to_search();
    void check_goal_conditions(grid* gp);
    
    
    void search_left(grid* gp, tree* tp);
    void search_up(grid* gp, tree* tp);
    void search_down(grid* gp, tree* tp);
    void search_right(grid* gp, tree* tp);
    
    
    void check_boundaries(grid* gp); 
    void prune(tree* tp); 
    void expansion_prune(tree* tp); 
    void check_move(grid* gp, tree* tp); 
    
    
    void update_node_count(tree* tp);
    void set_new_search_point(tree* tp);
    
    
    int best; 
    int lev; 
    int n_nodes; 
    bool action_checker; 
    int node_number; 
    int parent_number; 
    double prune_x; 
    double prune_y; 
    
    
    int step_count; 
    
    
    bool expansion;
    bool optimal_path; 
    double ax; 
    double ay; 
    double previous_x; 
    double previous_y; 
    
};

#endif 
