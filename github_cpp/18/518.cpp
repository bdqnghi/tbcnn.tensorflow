/*
  Name: string-reverse.cpp
  Copyright: 2008
  Author: Anurag Bhandari
  Date: 11-08-08 23:16
  Description: Reverses the input string
*/

#include<iostream>
#include<string>

using namespace std;

int main()
{
    char arr[10];
    cout<<"Input the string: ";
    gets(arr); //we use gets instead of cin to be able to include spaces too
    int length = strlen(arr);
    cout<<"\nThe reversed string is:"<<endl<<endl;
    for(int i=length-1; i>=0; i--) //length-1 because we do not want to print the null character
    {
            cout<<arr[i];
    }
    cout<<"\n\n";
    system("PAUSE");
    return(0);
}
