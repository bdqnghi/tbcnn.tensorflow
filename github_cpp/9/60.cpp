//reversing a string, iteratively and recursively
//Toy
// 08.09.2013

#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
	string data;
	char temp;
	
	cout << "Enter a string to be reversed: ";
	cin >> data;
	
	//swap from and back while not at the middle
	for(unsigned int i = 0; i != data.length() / 2; i++)
	{
		//stores current front value of string
		temp = data[i];
		//set front value to end value
		data[i] = data[data.length()-1-i];
		//end value = front value
		data[data.length()-i-1] = temp;
	
	}

	cout << "\nString reverse is: " << data << "\n";

	


}