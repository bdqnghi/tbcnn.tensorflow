#include <iostream>
using namespace std;

void stringReverse(char* ,int);
int main()
{
    char* a=new char;
    cout<<"Enter a string:";
    cin>>a;
    int size=strlen(a);
    
    cout<<endl<<"The string reversed is: ";
    stringReverse(a,(size-1));
    
    cout<<endl;
    system("pause");
    return 0;
}

void stringReverse(char* a,int s)
{
    if(s==0)
    {
        cout<<*(a);
        return;
    }
    else
    {
       cout<<*(a+s);
       stringReverse(a,(s-1));
       return;
    }  
}
