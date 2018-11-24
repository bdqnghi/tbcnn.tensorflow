#include <catch.hpp>

#include "AVL-tree.hpp"

/*           10            */
TEST_CASE("insert1", "[root]") 
{
   AVL_tree<int> tree;
   tree.insert(10);
   REQUIRE(tree.left(10) == nullptr);
   REQUIRE(tree.right(10) == nullptr);
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.height(tree.search(10)) == 1);
   REQUIRE(tree.count() == 1);
}

/*        10             9
         /             /   \       
        9      ->     8     10        
      /
     8                           */
TEST_CASE("insert2", "[rotate_right]") 
{
   AVL_tree<int> tree;
   tree.insert(10);
   tree.insert(9);
   tree.insert(8);
   REQUIRE(tree.left(9) == tree.search(8));
   REQUIRE(tree.right(9) == tree.search(10));
   REQUIRE(tree.parent(9) == nullptr);
   REQUIRE(tree.root() == tree.search(9));
   REQUIRE(tree.height(tree.search(9)) == 2);
   REQUIRE(tree.parent(8) == tree.search(9));
   REQUIRE(tree.parent(10) == tree.search(9));
   REQUIRE(tree.height(tree.search(8)) == 1);
   REQUIRE(tree.height(tree.search(10)) == 1);
   REQUIRE(tree.count() == 3);
}

/*  8                        9
      \                    /   \       
        9           ->    8     10        
          \
           10                     */
TEST_CASE("insert3", "[rotate_left]") 
{
   AVL_tree<int> tree;
   tree.insert(8);
   tree.insert(9);
   tree.insert(10);
   REQUIRE(tree.left(9) == tree.search(8));
   REQUIRE(tree.right(9) == tree.search(10));
   REQUIRE(tree.parent(9) == nullptr);
   REQUIRE(tree.root() == tree.search(9));
   REQUIRE(tree.height(tree.search(9)) == 2);
   REQUIRE(tree.parent(8) == tree.search(9));
   REQUIRE(tree.parent(10) == tree.search(9));
   REQUIRE(tree.height(tree.search(8)) == 1);
   REQUIRE(tree.height(tree.search(10)) == 1);
   REQUIRE(tree.count() == 3);
}

/*        9                9
        /   \     ->     /
       8     10         8        */
TEST_CASE("delete1", "[leaf]") 
{
   AVL_tree<int> tree;
   tree.insert(8);
   tree.insert(9);
   tree.insert(10);
   REQUIRE(tree.count() == 3);
   tree.deleteElement(10);
   REQUIRE(tree.root() == tree.search(9));
   REQUIRE(tree.height(tree.search(8)) == 1);
   REQUIRE(tree.height(tree.search(9)) == 2);
   REQUIRE(tree.right(9) == nullptr);
   REQUIRE(tree.count() == 2);
}

/*        9                9
        /   \     ->     /   \
       8     10         7     10    
      /                          
     7                            */
TEST_CASE("delete2") 
{
   AVL_tree<int> tree;
   tree.insert(8);
   tree.insert(9);
   tree.insert(10);
   tree.insert(7);
   REQUIRE(tree.height(tree.search(7)) == 1);
   REQUIRE(tree.height(tree.search(10)) == 1);
   REQUIRE(tree.height(tree.search(8)) == 2);
   REQUIRE(tree.height(tree.search(9)) == 3);
   REQUIRE(tree.count() == 4);
   tree.deleteElement(8);
   REQUIRE(tree.root() == tree.search(9));
   REQUIRE(tree.height(tree.search(7)) == 1);
   REQUIRE(tree.height(tree.search(10)) == 1);
   REQUIRE(tree.height(tree.search(9)) == 2);
   REQUIRE(tree.left(9) == tree.search(7));
   REQUIRE(tree.count() == 3);
}

/*        9                10
        /   \     ->     /
       8     10         8        */
TEST_CASE("delete3", "[node->right]") 
{
   AVL_tree<int> tree;
   tree.insert(8);
   tree.insert(9);
   tree.insert(10);
   REQUIRE(tree.count() == 3);
   tree.deleteElement(9);
   REQUIRE(tree.root() == tree.search(10));
   REQUIRE(tree.height(tree.search(8)) == 1);
   REQUIRE(tree.height(tree.search(10)) == 2);
   REQUIRE(tree.left(10) == tree.search(8));
   REQUIRE(tree.right(10) == nullptr);
   REQUIRE(tree.parent(10) == nullptr);
   REQUIRE(tree.count() == 2);
}
