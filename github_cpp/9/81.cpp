

#include<iostream>
#include<string>

using namespace std;

int main()
{
    char arr[10];
    cout<<"Input the string: ";
    gets(arr); 
    int length = strlen(arr);
    cout<<"\nThe reversed string is:"<<endl<<endl;
    for(int i=length-1; i>=0; i--) 
    {
            cout<<arr[i];
    }
    cout<<"\n\n";
    system("PAUSE");
    return(0);
}
