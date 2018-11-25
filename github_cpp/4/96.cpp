#include<iostream>

using namespace std;

void towerOfHanoi(int m,char from,char to,char temp,int& count);

int main()
{
    int count = 0;
    int noOfDisks;
    cout<<"Enter no of disks: ";
    cin>>noOfDisks;
    cout<<"###STEPS###"<<endl;
    towerOfHanoi(noOfDisks,'A','B','C',count);
    cout<<endl<<"Total number of stops: "<<count<<endl;
    return 0;
}

void towerOfHanoi(int m,char from,char temp,char to,int& count){
    count++;
    if(m==1)
    {
        cout<<"Move "<<m<<" from "<<from<<" to "<<to<<endl;
    }
    else
    {
        towerOfHanoi(m-1,from,to,temp,count);
        cout<<"Move "<<m<<" from "<<from<<" to "<<to<<endl;
        towerOfHanoi(m-1,temp,from,to,count);
    } 
}