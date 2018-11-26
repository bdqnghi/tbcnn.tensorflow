// main.cpp
// Print string backward.
#include <iostream>
#include <string>

void stringReverse( std::string, size_t = 0 );

int main()
{
	std::cout << "Input string: ";
	std::string strInput;
	std::getline( std::cin, strInput );

	std::cout << "Reverse string: ";
	stringReverse( strInput );
	std::cout << std::endl;

	return 0;	
}

///
/// print reverse string from starting position
/// "start"
void stringReverse( std::string str, size_t start ) 
{
	if ( start < str.length() ) 
	{
		size_t last = str.length() - 1 - start;
		std::cout << str[ last ];
		// next character
		++start;
		stringReverse( str, start );
	} else {
		return;
	}
}
