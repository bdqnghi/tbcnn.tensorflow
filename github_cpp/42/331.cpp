#include<iostream>
#include<vector>
#include<cstdlib>
#include "time-it.cpp"

using namespace std;

int size;

template<typename T>
void selection_sort(vector<T> &array)
{
    int i,j,min;
    T temp;
    for(i=0;i<array.size()-1;i++)
    {
        min=i;
        for(j=i;j<array.size();j++)
        {
            if(array[min]>array[j])
            min=j;              //holding the index of the smallest element
        }
        temp=array[i];          //swapping of the elements
        array[i]=array[min];
        array[min]=temp;
    }
}
int main(int argc, char *argv[])
{
    try
    {
        double exetime;
        cin>>size;
        vector<int> vec(size); //Change vector parameter as required
        int i;
        for(i=0;i<size;i++)
        {
            cin>>vec[i];
        }
        exetime=time_it(selection_sort,vec);
        cout<<"The sorted array is: ";
        for(i=0;i<size;i++)
        {
            cout<<vec[i]<<" ";
        }
        cout<<endl;
        cout << "sorted under " << exetime<< " seconds." << endl;
    }
    catch(...)
    {
        cout<<"An error has occurred , check the input"<<endl;
        return 1;
    }
    return 0;
}
