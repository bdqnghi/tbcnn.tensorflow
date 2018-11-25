
#include<iostream>
#include<math.h>
#include<string>
#include<cstring>
#include"quick.h"
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <locale>
#include <sstream>
#include <queue>


using namespace std;

    quick::quick()
    {

    }
	quick::quick(int x[], int elements, int pivot)
	{
		elementsNum = elements;
		sort(x,pivot, 0, (elements - 1));
	}
	void quick::sort(int x[],int pivot, int partB, int partE)
	{
        int z;int i = partB + 1;int a,b = 0;
        a = partB + 1;

        if(pivot == partB)
        {
            pivot++;
        }
        if(pivot != 0)
        {
                z = x[pivot];
                x[pivot] = x[partB];
                x[partB] = z;

               while(i <= partE)
               {
                    if(x[i] <= x[partB])
                    {
                        if(partE-partB == 1)
                        {
                            z = x[partB];
                            x[partB] = x[a];
                            x[a] = z;
                            a++;
                        }
                        else
                        {
                            z = x[i];
                            x[i] = x[a];
                            x[a] = z;
                            a++;
                            b = 1;
                        }
                    }
                    i++;
               }
                if(b == 1)
                {
                    z = x[a-1];
                    x[a-1] = x[partB];
                    x[partB] = z;
                }

                if(b == 1)
                {
                    if(((a-2) != partB))
                    {
                        sort(x,(((a-2) - partB)/2) + partB,partB,(a-2));
                    }
                }

             if((partE != a) && a < partE)
             {
                 sort(x,(((partE) - a)/2) + a,a,partE);
             }

        }
	}

