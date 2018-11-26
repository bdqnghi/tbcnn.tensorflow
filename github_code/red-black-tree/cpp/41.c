//
//  red_black_tree.hpp
//  ADS Project
//
//  Created by Abhinav Rathi on 3/22/16.
//  Copyright © 2016 Abhinav Rathi. All rights reserved.
//

#ifndef red_black_tree_hpp
#define red_black_tree_hpp

struct node{
    int ID;         // ID of Event Counter
    int count;      // No. of Events associated with the ID
    char color;     // b for black; r for red
    node *p;        // Parent Pointer
    node *l;        // Left Child Pointer
    node *r;        // Right Child Pointer
    
    // Constructor
    node(int i, int c){
        ID=i;
        count=c;
        color='b';  // Making All Nodes Black, Handling Case of Making Red within function call
        p=NULL;
        l=NULL;
        r=NULL;
    }
};

class red_black_tree{
    
private:
    node *root;
    
public:
    // Required Functions
    red_black_tree();                       // Constructor
    void insert_from_sorted_list(int id[],int count[],int start,int end,int height); // Tree Initialization
    int increase(int id,int m);             // Increase count of "id" by "m", if present else insert
    int reduce(int id,int m);               // Reduce count of "id" by "m", if present else insert
    int count(int id);                      // Return count of "id"
    int inrange(int id1,int id2);           // Total count of events between "id1" & "id2"
    node* search(int id);                   // Search for "id" in Red-Black-Tree
    node* search_next(int id);              // Search next of "id", given "id" is not present in Tree
    node* search_previous(int id);          // Search previous of "id", given "id" is not present in Tree
    
    // Above functions use the under-mentioned functions
    void insert(node *t);                   // Insert single node "t" into Red-Black-Tree
    void remove(node *t);                   // Removes node "t" from Red-Black-Tree
    node* next(node *t);                    // Search for next node of a given node "t"
    node* previous(node *t);                // Search for previous node of a given node "t"
    node* getroot();                        // Return root of Red-Black-Tree
    node* sorted_insert(int i[],int c[],int s,int e,int h); // Recursive Tree Initialization (Sorted List)
    int inrange_recursive(node *t,int i1,int i2);   // Recursive function for tree traversing and counting
    
    // Extra Functions Implimented
    void display(node *t,int n,char c);     // Display Red-Black-Tree
    int max_height(node *t);                // Returns Maximum Height of Tree
    void color(node *t,int h);              // Colors all nodes black except last level (given bbst)
};

#endif /* red_black_tree_hpp */
