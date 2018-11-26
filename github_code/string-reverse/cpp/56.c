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

/*
string stringReverse(string str)
{
  char temp;
  int i, j;

  for(i = 0, j = str.length() - 1; i < str.length()/2; i++, j--)
  {
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
  return str;
}
*/
/*
string stringReverse(string str)
{
  if(str.length() == 1)  return str;

  string res = "";

  res += stringReverse(str.substr(1, str.length() - 1));
  res += str.substr(0, 1);
//  res.append(str, 0, 1);

  cout << res << endl;

  return (res);
}
*/

int main()
{
  "wolleh" == stringReverse("hellow") ? cout << "PASS\n" : cout << "FAIL\n";
  "olleh"  == stringReverse("hello")  ? cout << "PASS\n" : cout << "FAIL\n";
}
