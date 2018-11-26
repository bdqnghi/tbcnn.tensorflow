#include <vector>

using std::vector;

void quicksort(vector<int>& list)
{
    if (list.size()  == 0 || list.size() == 1)
    { }
    else if (list.size() == 2)
    {
        if (list[0] > list[1])
        {
            int x = list[0];
            list[0] = list[1];
            list[1] = x;
        }
    }
    else if (list.size() > 2)
    {
        std::vector<int> left;
        std::vector<int> right;

        int pivot = list[0];
        for(int i = 1; i < list.size(); ++i)
        {
            if (list[i] <= pivot)
            {
                left.push_back(list[i]);
                               
            }
            else
            {
                right.push_back(list[i]);               
            }
           
        }
        left.push_back(pivot);
        quicksort(left);
        quicksort(right);

        int k = 0;
        for (int i = 0; i < left.size(); ++i)
        {
            list[k++] = left[i];
        }

        for (int i = 0; i < right.size(); ++i)
        {
            list[k++] = right[i];
        }
    }
}

