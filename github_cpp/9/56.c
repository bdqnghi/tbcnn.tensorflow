#include <iostream>
#include <string>
using namespace std;

string stringReverse(string str)
{
  int i;
  string res = "";

  for(i = str.length() - 1; i >= 0; i--)
  {
    res.append(1, str[i]);
  }
  return res;
}




int main()
{
  "wolleh" == stringReverse("hellow") ? cout << "PASS\n" : cout << "FAIL\n";
  "olleh"  == stringReverse("hello")  ? cout << "PASS\n" : cout << "FAIL\n";
}
