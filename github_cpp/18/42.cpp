// reverseString.cpp
// this is exercise 1.20 in the Schaum book.
#include <iostream>
#include <string>

 void reverseString(std::string& inputString);

int main(void)
{
	std::cout << "Enter a string:" << std::endl;
	std::string inputString;
	std::cin >> inputString;
	std::cout << "This is what you entered: " << inputString << std::endl;
	reverseString(inputString);
	std::cout << "This is the reverse: " << inputString << std::endl;
	return 0;
}

void reverseString(std::string& inputString)
{
	char temp = 0;
	int len = inputString.length();
	std::cout << len << std::endl;
	for(int i = 0; i < len/2; i++)
	{
		std::cout << inputString[i] << std::endl;
		temp = inputString[i];
		inputString[i] = inputString[len - 1 - i];
		inputString[len - 1 - i] = temp;
	}
}