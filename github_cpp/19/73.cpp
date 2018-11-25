



#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class quickSort
{
public:
    quickSort();
    ~quickSort();
    void generateData(int);
    int getLength();
    short getItem(int);
    void printData();
    void quick_Sort();
private:
    int length;
    short *myArray;
    static const int LIMIT = 5000;
    void quick_Sort(int, int);
    int partition(int, int);
};


quickSort :: quickSort()
{
    length = 0;                         
    myArray = NULL;                     
}


quickSort :: ~quickSort()
{
    delete [] myArray;                  
}



void quickSort :: generateData(int n)
{
    length = n;                         
    myArray = new short [length];       

    for (int i = 0; i < length; i++)
        myArray[i] = rand() % LIMIT;    

}


int quickSort :: getLength()
{
    return length;                      
}



short quickSort :: getItem(int index)
{
    if (index <= length)                
        return myArray[index];          

    else if (index > length)    {       
        cout << "Invalid value!" << endl;
        return 0;                       
    }

    return 0;                           
}


void quickSort :: printData()
{
    for (int i = 0; i < length; i++)
      {
        ((i % 10) == 9) ? cout << setw(6) << myArray[i] << '\n' : cout << setw(6) << myArray[i] << ' ';
      }
}


void quickSort :: quick_Sort()
{
    return quick_Sort(0, length - 1);        
}


void quickSort :: quick_Sort(int low, int high)
{
    int p;

    if (low < high)
    {
        p = partition(low, high);           
        quick_Sort(low, p);                 
        quick_Sort(p+1, high);              
    }
}


int quickSort :: partition(int low, int high)
{
    int pivot = myArray[low];               
    int i = low - 1;                        
    int j = high + 1;                       
    while(true)
    {
        do {
            i++;                            
        } while (myArray[i] > pivot);       
        do {
            j--;                            
        } while (myArray[j] < pivot);       
        if (i < j)                          
        {
            swap(myArray[i], myArray[j]);   
        }
        else
            return j;                       
    }
}
