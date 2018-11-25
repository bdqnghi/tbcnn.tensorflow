


#include <iostream>
#include "stack.h"
using namespace std;

class Hanoi {
   friend void TowersOfHanoi(int);
   public:
      void TowersOfHanoi(int n, int x, int y, int z);
   private:
      Stack<int> *S[4]; 
};

void Hanoi::TowersOfHanoi(int n, int x, int y, int z)
{
 
   int d;  
   if (n > 0) {
      TowersOfHanoi(n-1, x, z, y);
      S[x]->Delete(d);  
      S[y]->Add(d);  
   
   
      cout << "Move disk " << d << " from tower "
           << x << " to tower " << y << endl;
      TowersOfHanoi(n-1, z, y, x);}
}

void TowersOfHanoi(int n)
{
   Hanoi X;
   
   X.S[1] = new Stack<int> (n);
   X.S[2] = new Stack<int> (n);
   X.S[3] = new Stack<int> (n);
   
   for (int d = n; d > 0; d--) 
      X.S[1]->Add(d); 
   
   
   
   X.TowersOfHanoi(n, 1, 2, 3);
}

int main()
{
   cout << "Moves for a three disk problem are" << endl;
   TowersOfHanoi(3);
   system("pause");
   return 0;
}

