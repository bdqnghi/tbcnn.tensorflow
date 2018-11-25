#include <iostream>
#include <string.h>

template <class SType>
void select(SType *item, int count);

using namespace std;

int main()
{
    char str[] = "dcab";
    select(str, (int)strlen(str));
    cout << "Sorted string: " << str << endl;
    
    int nums[] = {5, 4, 6, 3, 2, 7, 1};
    int arr_len = sizeof(nums)/sizeof(*nums);
    select(nums, arr_len);
    for (int i = 0; i < arr_len; ++i)
    {
        cout << nums[i] << " ";
    }

    return 0;
}

template <class SType>
void select(SType *item, int count)
{
    int a, b, c;
    int exchange;
    SType t;
    for (a = 0; a < count-1; ++a)
    {
        exchange = 0;
        c = a;
        t = item[a];
        for (b = a+1; b<count; ++b)
        {
            if (item[b] < t)
            {
                c = b;
                t = item[b];
                exchange = 1;
            }
        }
        if (exchange)
        {
            item[c] = item[a];
            item[a] = t;
        }
    }
}
