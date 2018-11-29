#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>

using namespace std;

int size;

template<class T>
void shell_sort(vector<T> &array)
{
    int i,j,h=1;
    T temp;
    while(h<size/3)
    h=3*h+1;                                //following the knuth series
    while(h>0)
    {
        for(i=h;i<size;i+=h)
        {
            for(j=i;j>0;j-=h)
            {
                if(array[j]<array[j-h])
                {
                    temp=array[j-h];          //swapping of the elements
                    array[j-h]=array[j];
                    array[j]=temp;
                }
                else break;
            }
        }
        h/=3;                                  //reducing the back step
    }
}

template<class T>
double time_it(void (*action)(vector<T>&), vector<T> &arg) {
  clock_t start_time = clock();
  action(arg);
  clock_t finis_time = clock();
  return ((double) (finis_time - start_time)) / CLOCKS_PER_SEC;
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
        exetime=time_it(shell_sort,vec);
        //shell_sort(vec);
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
