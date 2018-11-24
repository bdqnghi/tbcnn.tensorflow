/*
C++ matrix multiplication example.

In matrix multiplication first matrix one row element is multiplied by second matrix all column elements.

Goto: https://www.javatpoint.com/matrix-multiplication-in-cpp
*/

#include<iostream>
using namespace std;

int main()
{
    int matA[3][3], matB[3][3], matC[3][3];

    cout<<"Enter elements of Matrix A"<<endl;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            cout<<"A["<<i<<"]["<<j<<"] = ";
            cin>>matA[i][j];
        }
    }

    cout<<"Enter elements of Matrix B"<<endl;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            cout<<"B["<<i<<"]["<<j<<"] = ";
            cin>>matB[i][j];
        }
    }

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            matC[i][j]=0;
        }
    }

    for(int i=0; i<3;i++)
    {
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                int sum=0;
                matC[i][j]+=matA[i][k]*matB[k][j];
            }
        }
    }

    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            cout<<"C["<<i<<"]["<<j<<"] = ";
            cout<<matC[i][j]<<endl;
        }
    }


    return 0;
}
