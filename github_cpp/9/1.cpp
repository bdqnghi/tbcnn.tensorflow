

#include <iostream> 
#include <string>
using namespace std;

void stringReverse( string, size_t );

int main()
{
   string s = "Print this string backward.";
   cout << s << '\n'; 

   stringReverse( s, 0 ); 
   cout << endl;
}


void stringReverse( string stringToReverse, size_t startSubscript )
{
	static size_t stringSize = stringToReverse.size();

	if(stringSize == (startSubscript + 1))
		cout << stringToReverse[startSubscript];
	else
	{
		cout << stringToReverse[(stringSize -1 )];
		--stringSize;
		stringReverse(stringToReverse, startSubscript);
	}

}