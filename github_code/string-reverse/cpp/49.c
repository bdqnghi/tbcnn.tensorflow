/**
* Perform string reversing operation
* author Md Asadul Islam<mdasadul@ualberta.ca>
*/
#include<iostream>
#include<string>
using namespace std;

class StringReverse
{
private:
    string inputString;
public:
    void getString();
    void getReverse();
    void displayString();
};
void StringReverse::getString()
{
    getline(cin, inputString);
}
void StringReverse::getReverse()
{
    int i,j;
    char c;
    for(i=0,j=inputString.length()-1;i<inputString.length()/2;i++,j--)
    {
       c=inputString[i];
       inputString[i] = inputString[j];
       inputString[j] = c;
    }
}
void StringReverse::displayString()
{

    cout << inputString;
}

int main()
{

    StringReverse stringObj;
    stringObj.getString();

    stringObj.getReverse();
    stringObj.displayString();

}
