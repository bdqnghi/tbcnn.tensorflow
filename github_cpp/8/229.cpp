//*******************************************
//
// Author: Brian Rundel
// This program will use the fibonacci number
// position to caculate the number
//*******************************************

#include <iostream>

using namespace std;

int main()
{
     int counter;
     int num1,num2,current;
     int postion;

     cout << "Enter the first number. ";
     cin >> num1;
     cout << "Enter the second number. ";
     cin >> num2;
     cout << "Enter the position of the number. ";
     cin >> postion;
     if( num1 == 1 )
     {
         current = num1;
     }
     else if ( num1 == 2)

         current = num2;
     else
     {
         counter = 3;
         while (counter <= postion)
         {
             current = num2 + num1;
             num1 = num2;
             num2 = current;
             counter++;
         }

     }
       cout << "The number is " << current << " at "
             << "position " << postion << endl;
      return 0;
}
