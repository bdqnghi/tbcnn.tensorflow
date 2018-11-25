


#include <iostream>
#include <iterator>

using namespace std;




template<class T> void bubble_sort(T[], int);
int main(int args, char** argv)
{
    int ia[] = {1, 9, 5, 4, 8, 0, 2, 3, 7, 9};
    int size = sizeof(ia)/sizeof(int);

    bubble_sort(ia, size);
    copy(ia, ia+size, ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}

template<class T> 
void bubble_sort(T s[], int size)
{
    for (int i=0; i<size; i++)
    {
        bool change = false;
        int index = 0;
        for (int j=index+1; j<size-i; j++)
        {
            if (s[j] < s[index])
            {
                swap(s[index], s[j]);
                change = true;
            }
            index = j;
        }
        if (!change)
            break;
    }
}
