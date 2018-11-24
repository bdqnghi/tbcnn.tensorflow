#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class letter{
public:
    string letter_line;
  int size;
  int new_size;
  string new_letter_line;
  int j;
  string palin_line;
  int palin_size;
private:
  void removeNoLetters();
  void lowerCase();
  void isPalindrome();
};

void letter::removeNoLetters(){
    for(int i=0;i<letter_line.size(); i++){
        if ((letter_line[i]<'z'&&letter_line[i]>'a')||(letter_line[i]>'A'&&letter_line[i]<'Z')){
            new_letter_line[j]=letter_line[i];
            }
            cout<<new_letter_line[j]<<endl;
            j=j++;
    }
  }

void letter::lowerCase(){
  for (int i=0;i<letter_line.size();i++){
    if (letter_line[i]>'A'&&letter_line[i]<'Z')
      {letter_line[i]=letter_line[i]-32;
      }
      cout<<letter_line[i]<<endl;
  }
}

void letter::isPalindrome(){
  for(int i=0;i<letter_line.size();i++)
    {palin_line[letter_line.size()-i]=letter_line[i];
      cout<<palin_line[letter_line.size()-i];
    }
}

