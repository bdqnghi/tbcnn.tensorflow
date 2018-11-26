/* Copyright (c) 2015, Thomas Lang. All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <iostream>
#include "RedBlackTree.h"
using namespace std;

// Testing function.
int main(int argc, char* argv[])
{
    cout << "Creating a new Red-Black-Tree ... ";
    RedBlackTree<int> test;
    cout << "done." << endl;
    cout << "Inserting some values ... ";
    test.insert(7);
    test.insert(8);
    test.insert(6);
    test.insert(12);
    test.insert(0);
    test.insert(9);
    test.insert(10);
    test.insert(-7);
    test.insert(999);
    cout << "done." << endl;
    cout << "Tree now: " << test << endl;
    cout << "Deleting a few values ... ";
    test.remove(12);
    test.remove(0);
    test.remove(9);
    test.remove(7);
    test.remove(8);
    test.remove(10);
    test.remove(-7);
    test.remove(6);
    cout << "done." << endl;
    cout << "Tree now: " << test << endl;
    
    cout << "Clearing tree now ... ";
    test.clear();
    cout << "done." << endl;
    cout << "Tree now: " << test << endl;
    return 0;
}
