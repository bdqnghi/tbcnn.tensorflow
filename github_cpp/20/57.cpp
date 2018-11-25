


#include <iostream>
#include <cstring>
#include <fstream>
#include <stdlib.h> 
#include "rbtree.h"

using namespace std;

int main() {
  RBTree tree;
  char method;

  char fileName[30];
  ifstream inFile;
  
  cout << "Welcome to the Red Black Tree Program; we will balance your tree!  Enter the name of your file: " << endl;
  cin >> fileName;
  inFile.open(fileName);
  if(!inFile) {
      cout << "Error: No such file." << endl;
      return 0;
  }
  string token;
  while(getline(inFile, token, ',')) { 
    int num = atoi(token.c_str()); 
    if (num > 0) {
      tree.add(num);
    }
  }
  
  while (method != 'Q') {
    cout << "Available commands: Add (A), Print (P), Search (S), Remove (R), Quit (Q).  Enter your command: " << endl;
    cin >> method;
    
    if (method == 'A') {
      int val;
      cout << "Enter value: " << endl;
      cin >> val;
      tree.add(val);
    } else if (method == 'P') {
      tree.print();
    } else if (method == 'S') {
      int val;
      cout << "Enter value: " << endl;
      cin >> val;
      tree.search(val);
    } else if (method == 'R') {
      int val;
      cout << "Enter value: " << endl;
      cin >> val;
      if (val > 0) {
	tree.remove(val);
      } else {
	cout << "Error: No zeroes allowed" << endl;
      }
    } else if (method == 'Q') {
      break;
    } else {
      cout << "Error: Invalid command." << endl;
    }
  }

  return 0;
}
