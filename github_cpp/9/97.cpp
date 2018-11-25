


#include <iostream>
#include <string>
using namespace std;

string reverse(string str);
string reverse(string str, string strRev);

int main()
{
	string strPhrase, strReversePhrase;
	
	
	cout << "Reverse" << endl;
	cout << "Phrase to reverse: ";
	getline(cin, strPhrase);

	
	for (int i = strPhrase.length(); i >= 0; i--)
	{
		strReversePhrase += strPhrase.substr(i, 1);
	}
	cout << "Phrase in reverse (using iteration): " << strReversePhrase << endl;

	
	strReversePhrase = reverse(strPhrase);
	cout << "Phrase in reverse (using recursion): " << strReversePhrase << endl;

	system("pause");
	return 0;
}


string reverse(string str)
{
	return reverse(str, "");
}




string reverse(string str, string strRev)
{
	if (str.length() == 0)
	{
		return strRev;								
	}
	else
	{
		strRev += str.substr(str.length() - 1, 1);	
		str = str.substr(0, str.length() - 1);	    
		return reverse(str, strRev);				
	}
}
