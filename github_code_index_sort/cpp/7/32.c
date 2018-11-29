#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    void shellsort(int* array,int n);
    int a[10]={49,38,65,97,76,13,27,49,55,4};
    shellsort(a,10);
    for(int i=0;i<10;i++)
        cout<<a[i]<<' ';
    system("PAUSE");
    return EXIT_SUCCESS;
}
void shellsort(int* array,int n)
{
    void shell(int* array,int n,int d);
    for(int i=n/2;i>0;i/=2)
    {
        shell(array,n,i);        
    }
}
void shell(int* array,int n,int d)
{
    for(int i=d;i<n;i++)
    {
        int temp=array[i];
        int j;
        for(j=i-d;j>=0;j-=d)
        {
            if(temp<array[j])
                array[j+d]=array[j];
            else 
                break;    
        }
        array[j+d]=temp;
    }              

}
