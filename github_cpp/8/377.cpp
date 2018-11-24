#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>

using std::cout;
using std::endl;

int getFib(int n)
{
     if (n == 0)
	  return 0;
     else if (n == 1)
	  return 1;
     else if (n > 1) {
	  return (getFib(n-1) + getFib(n-2));
     }
}


int main(int argc, char *argv[])
{
     // number of elements to display in series
     if (argc != 2) {
	  cout << "ERROR: Need to input the number of elements to display." << endl;
	  return 1;
     }
     int N = atoi(argv[1]);

     // sanity check
     if (N < 1) {
	  cout << "ERROR: Need to ask for 2 or more values." << endl;
	  return 1;
     }

     // display
     for (int i = 0; i < N; i++) {
	  cout << getFib(i);
	  if (i < N-1)
	       cout << ", ";
     }
     cout << endl;

     return 0;
}
