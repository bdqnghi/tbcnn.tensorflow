#include <iostream>
#include <vector>
#include "../util/show.cpp"
using namespace std;

template <class T>
class InsertionSort
{
    bool less (vector<int> bag, int i, int j)
    {
        return bag[i] < bag[j];
    }
    void exch(vector<int>& bag, int i, int j)
    {
        auto t = bag[i];
        bag[i] = bag[j] ;
        bag[j] = t;
    }
public:
    InsertionSort(vector<int> bag)
    {
        for(int i = 0; i < bag.size(); i ++)
        {
            for (int j = i; j > 0; j--)
            {
                if(less(bag, j, j-1)) exch(bag, j, j-1);
                else break;
            }
        }
        showVector(bag);
    }
};

int main()
{
    InsertionSort<int> sort({1, 3, 5, 2, 8, 2, 9, 0});
}