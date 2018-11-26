//
//  cpp project.cpp
//  c++
//
//  Created by Apple on 26/05/17.
//
//

#include "cpp project.hpp"
#incldue <stdio.h>
#include <iostream.h>
#incldue <conio.h>

int maing()
{
    clrscr();
    int arr1[30][30], arr2[20][20];
    int result[20][20];
    int m,n;
    int i,j;
    
    cout << "enter the number of rows (m):";
    cout << "enter the number of coloumns (n):";
    cout << "enter the elements within the first matrix \n";
    
    for (i=0; i<m; i++) {
        for(j=0;j<n;J++){
            
            cout << " element "<< i <<" : "<<j<<" -->";
            cin << arr1[i][j];
        }
    }
    cout << "enter the elements within the second matrix \n";
    for (i=0; i<m; i++) {
        for(j=0;j<n;J++){
            
            cout << " element "<< i <<" : "<<j<<" -->";
            cin << arr2[i][j];
        }
    }
    
    cout << "\n first matric \n";
    for(i=0; i<m;i++){
        for(j=0;j<n;j++)
        {
            cout << "" << arr1[i][j];
        }
        cout << "\n";
    }
    cout << "\n second matric \n";
    for(i=0; i<m;i++){
        for(j=0;j<n;j++)
        {
            cout << "" << arr2[i][j];
        }
        cout << "\n";
    }
    
    cout << " \n Resultant matric is \n";
    
    int k=0;
    
    for(i=0;i<m; i++)
    {
        for( j=0; j<n;j++)
        {
            result[i][j] =0;
            
            for(k=0;k<m;k++)
            {
                result[i][j]= result[i][j] + arr1[i]k] * arr2[k][j];
            }
        }
    }
    for(i=0;i<m; i++)
    {
        for( j=0; j<n;j++)
        {
            cout << result[i][j] << "";
        }
        cout << "\n\n";
    }
    return 0;
}
