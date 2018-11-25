





#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int SIZE = 10;

void bucket_sort(double A[], int n)
{
    vector< vector<double> > B;
    
    for (int i = 0; i < n; i++)
    {
        vector<double> v;
        B.push_back(v);
    }
    
    for (int i = 0; i < n; i++)
        B[n*A[i]].push_back(A[i]);

    
    for (int i = 0; i < n; i++)
        sort(B[i].begin(), B[i].end());

    
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (!B[i].empty())
        {
            for (vector<double> :: iterator it = B[i].begin(); 
                 it < B[i].end(); it++)
            {
                A[k++] = *it;
            }
        }
    }
}


int main(int argc, const char * argv[])
{
    double a[SIZE] = {0.78,0.17,0.39,0.26,0.72,
                      0.94,0.21,0.12,0.23,0.68};
    
    bucket_sort(a, SIZE);
    
    
    for (int i =0; i < SIZE; i++)
        cout << a[i] << " ";

    return 0;
}

