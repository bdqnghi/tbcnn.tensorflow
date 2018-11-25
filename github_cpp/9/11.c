
#include <iostream> 
#include <string>
using namespace std;

void stringReverse( string, int );

int main()
{
   string s = "Print this string backward.";
   cout << s << '\n'; 

   stringReverse( s, 0 ); 
   cout << endl;
} 


void stringReverse( string stringToReverse, int startSubscript )
{
   
   if ( startSubscript == stringToReverse.length() )
      return;

   
   stringReverse( stringToReverse, startSubscript + 1 );
   cout << stringToReverse[ startSubscript ]; 
} 




