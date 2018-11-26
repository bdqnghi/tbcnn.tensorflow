/* 
 * File:   main.cpp
 * Author: Nicholas Zerbel
 *
 * Created on January 20, 2017, 3:10 PM
 */

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
    
    //Search Functions
    void search_left(grid* gp, tree* tp);
    void search_up(grid* gp, tree* tp);
    void search_down(grid* gp, tree* tp);
    void search_right(grid* gp, tree* tp);
    
    //Pruning Functions
    void check_boundaries(grid* gp); //Check to make sure agent does not move beyond Gridworld boundaries
    void prune(tree* tp); //Makes sure the agent does not visit a state it visited previously
    void expansion_prune(tree* tp); //Makes sure the agent visits other actions when expanding the tree
    void check_move(grid* gp, tree* tp); //Check the move to see if it does not violate one of the rules
    
    //Tree Functions
    void update_node_count(tree* tp);
    void set_new_search_point(tree* tp);
    
    //Parameters
    int best; //Optimal number of steps to the goal
    int lev; //Current level of the tree
    int n_nodes; //Value representing the number of possible actions within each level of a tree
    bool action_checker; //T or F action is possible
    int node_number; //Tracks the current node number
    int parent_number; //Tracks the parent number
    double prune_x; //X coordinate used to check pruning
    double prune_y; //Y coordinate used to check pruning
    
    //Tree Expansion Parameters
    int step_count; //Used to track the number of steps the agent has taken
    
    //Agent Parameters
    bool expansion;
    bool optimal_path; //Only turns true when depth first has found the optimal path to the goal
    double ax; //Current agent x coordinate
    double ay; //Current agent y coordinate
    double previous_x; //Previous agent x coordinate
    double previous_y; //Previous agent y coordinate
    
};

#endif /* DEPTH_H */
