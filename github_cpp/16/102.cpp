


#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;




template<class T> void shell_sort(T[], int);

int main(int args, char** argv)
{
    int ia[] = {1, 9, 5, 4, 8, 0, 2, 3, 7, 9};
    int size = sizeof(ia)/sizeof(int);

    shell_sort(ia, size);
    copy(ia, ia+size, ostream_iterator<int>(cout, " "));
    cout << endl;
    return 0;
}


template<class T>
void shell_sort(T s[], int size)
{
    for (int increment=size/2; increment>0; increment/=2)
    {
        for (int i=0; i<size; i++)
        {
            int index = i;
            for (int j=i-increment; j>=0; j-=increment)
            {
                if (s[index] < s[j])
                {
                    swap(s[index], s[j]);
                    index = j;
                }
                else
                {
                    break;
                }
            }
        }
    }
}
