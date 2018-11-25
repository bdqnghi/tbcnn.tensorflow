#include <iostream>
#include <string>

using namespace std;
string reverseString(string tempString){
	int length=tempString.length()-1;
	char tempChar;
	//go to half way point of string, and swap increaseing index from 0 to decreasing index from last
	for (int i=0; i<length/2; i++){
		tempChar=tempString[i];
		tempString[i]=tempString[length-i];
		tempString[length-i]=tempChar;		
	}
	return tempString;

}


int main (int argc, char* argv[]){
	switch (argc){
		case 0:
		case 1: break;
		default:
			cout<<"Reverse of "<<argv[1]<<"\t"<<reverseString(argv[1])<<endl;
	}

	return 0;
}
