#include <iostream>

using namespace std;

void stringReverse(char *str, int start, int end)
{
  
  if(start >= end)
  {
    return;
  }

  
  char temp;
  temp = str[start];
  str[start] = str[end];
  str[end] = temp;

  stringReverse(str, start + 1, end - 1);

}

int main()
{
  char name[] = "Stephen Hawkingscl is my favourite teacher.";
  int length = sizeof(name) - 1;

  cout << length << endl;

  cout << "before : " << name << endl;

  int start = 0;
  int end;

  for(int i = 0; name[i] != NULL; i++)
  {
    if(name[i] == ' ')
    {
      end = i - 1;
      stringReverse(name, start, end);
      start = i + 1;
    }
  }
  end = length - 1;
  stringReverse(name, start, end);
  cout << "after : " << name << endl;

  return 0;
}
