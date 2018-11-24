#include <iostream>
#include <string.h>

template <class SType>
void bubble(SType *item, int count);

using namespace std;

int main()
{
    char str[] = "dcab";
    bubble(str, (int)strlen(str));
    cout << "Sorted string: " << str << endl;
    
    int nums[] = {5, 4, 6, 3, 2, 7, 1};
    int arr_len = sizeof(nums)/sizeof(*nums);
    bubble(nums, arr_len);
    for (int i = 0; i < arr_len; ++i)
    {
        cout << nums[i] << " ";
    }

    return 0;
}

template <class SType>
void bubble(SType *item, int count)
{
    int a, b;
    SType t;
    for (a = 1; a < count; ++a)
    {
        for (b = count-1; b >= a; --b)
        {
            if (item[b-1] > item[b])
            {
                t = item[b-1];
                item[b-1] = item[b];
                item[b] = t;
            }
        }
    }
}
