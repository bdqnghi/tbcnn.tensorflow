#include "btree.h"
#include "constants.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

using namespace std;


void small_test() {
    cout << "SMALL TEST: " << endl;
    Btree btree;
    cout << btree << endl;
    btree.insert(0);
    btree.insert(2);
    btree.insert(3);
    cout << btree << endl;
    btree.remove(0);
    cout << btree << endl;
    btree.remove(2);
    cout << btree << endl;
    btree.insert(2);
    cout << btree << endl;
    btree.insert(0);
    cout << btree << endl;
    btree.remove(2);
    cout << btree << endl;
    cout << "###########################" << endl;
    assert(btree.isValid());
}

//Test the spec example which is related to split
void splitTestFromSpec() {
    cout << "SPLIT TEST: " << endl;
    Btree btree;
    btree.insert(2); btree.insert(4);
    cout << btree << endl;
    btree.insert(5);
    cout << btree << endl;
    btree.remove(5); btree.remove(2); btree.insert(2);
    cout << btree << endl;
    btree.insert(3);
    cout << btree << endl;
    cout << "###########################" << endl;
    assert(btree.isValid());
}

//Test the spec example which is related to redistribution. You have to set BTREE_FANOUT to 3 and BTREE_LEAF_SIZE to 6
//in constants.h for testing the same case
void testForRedistribution() {
    cout << "REDISTRIBUTION TEST: " << endl;
    Btree btree;
    btree.insert(1);
    btree.insert(2);
    btree.insert(3);
    btree.insert(7);
    btree.insert(8);
    btree.insert(10);
    btree.insert(11);
    btree.insert(9);
    btree.insert(12);
    btree.insert(13);
    btree.insert(4);
    btree.insert(5);
    btree.insert(6);
    btree.insert(14);
    btree.insert(15);
    cout << btree << endl;
    
    btree.remove(9);
    cout << btree << endl;
    cout << "###########################" << endl;
    
    assert(btree.isValid());
}

//More comprehensive test for some edge cases. The last step("btree.remove(1)") tests the spec example which is related
//to merging
void large_test1() {
    cout << "LARGE TEST1: " << endl;
    Btree btree;
    btree.remove(0); //test to remove while btree is empty
    cout << btree << endl;
    btree.insert(1); btree.insert(2);//initial inserts, make sure the root is leaf at the beginning
    cout << btree << endl;
    btree.insert(1); //test to insert an existing value
    cout << btree << endl;
    btree.remove(3); //test to remove nonexistent value
    btree.remove(1); //test to remove from root
    cout << btree << endl;
    btree.insert(1);
    cout << btree << endl;
    btree.insert(3); //test an insertion which causes root-split
    cout << btree << endl;
    btree.remove(3);
    cout << btree << endl; //////// add this line for debug 
    btree.remove(2);//test removals which makes the root leaf again
    cout << btree << endl;
    btree.insert(3); btree.insert(5); btree.insert(7); btree.insert(9); btree.insert(11); //insertions which cause splits
    cout << btree << endl;
    btree.insert(2); btree.insert(4); btree.insert(6); btree.insert(8); btree.insert(10); //more insertions
    cout << btree << endl;
    btree.remove(11); //Prefer redistribution over merging for removals
    cout << btree << endl;
    btree.remove(5); btree.remove(6); //Prefer redistribution with right node over left node
    cout << btree << endl;
    btree.remove(8); //Prefer merging with right node over left node.
    cout << btree << endl;
    btree.remove(3); btree.remove(2);
    cout << btree << endl;
    btree.remove(1);
    cout << btree << endl;
    cout << "###########################" << endl;
    
    assert(btree.isValid());
}

void large_test2() {
    cout << "LARGE TEST2: " << endl;
    Btree btree;
    btree.insert(1);
    btree.insert(2);
    btree.insert(3);
    btree.insert(4);
    btree.insert(6);
    btree.insert(8);
    btree.insert(13);
    btree.insert(15);
    btree.insert(17);
    cout << btree << endl;
    btree.insert(33);
    cout << btree << endl;
    btree.remove(13);
    cout << btree << endl;
    btree.remove(3);
    cout << btree << endl;
    
    btree.insert(10);
    cout << btree << endl;
    btree.insert(7);
    
    cout << btree << endl;
    btree.remove(8);
    cout << btree << endl;
    
    btree.remove(6);
    cout << btree << endl;
    btree.insert(18);
    cout << btree << endl;
    btree.insert(19);
    cout << btree << endl;
    btree.remove(17);
    cout << btree << endl;
    btree.insert(20);
    cout << btree << endl;
    btree.insert(34);
    cout << btree << endl;
    
    btree.insert(11);
    cout << btree << endl;
    btree.insert(12);
    cout << btree << endl;
    btree.insert(17);
    cout << btree << endl;
    
    btree.insert(13);
    cout << btree << endl;
    
    btree.remove(7);
    cout << btree << endl;
    btree.remove(2);
    cout << btree << endl;
    cout << "###########################" << endl;
    
    assert(btree.isValid());
}

//Random insertions to check the tree stays valid
void stress_insert(int itr) {
    // Stress-testing
    Btree btree;
    for (int i = 0; i < itr; ++i) {
        int num = rand() % itr*20;
        btree.insert(num);
        assert(btree.isValid());
    }
    
}



//Random deletes to check the tree stays valid
void stress_insert_delete(int itr) {
    // Stress-testing
    Btree btree;
    // insert a bunch of times - then delete it
    for (int i = 0; i < itr; ++i) {
        int num = rand() % itr*20;
        btree.insert(num);
        assert(btree.isValid());
    }
    
    
    for (int i = 0; i < itr; ++i) {
        int num = rand() % itr*20;
        btree.remove(num);
        assert(btree.isValid());
    }
}

int main() {
    std::string filename = std::string("expected_") + std::to_string(BTREE_FANOUT) + "_" + std::to_string(BTREE_LEAF_SIZE)
    + ".out";
    //freopen(filename.c_str(),"w",stdout); //Comment out if you want to write to a file. You should to set the
                                            //values in constants.h to create the corresponding output
    
    small_test();
    splitTestFromSpec();
    testForRedistribution();
    large_test1();
    large_test2();
    stress_insert(500);
    stress_insert_delete(500);
    
    return 0;
}
