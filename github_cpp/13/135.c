#include <stdio.h>
#include <stdlib.h>
#include <time.h>       

void bubbleSort(int* p, int length)
{
    int temp;
    int i, j;
    for (i = 1; i < length; i++) {
        for (j = 0; j < length - i; j++) {
            if (*(p + j) > *(p + j + 1)) {
                temp = *(p + j);
                *(p + j) = *(p + j + 1);
                *(p + j + 1) = temp;
            }
        }
    }
}
void merge(int* X, int x, int* Y, int y, int* Z)
{
    int i, j, k;
    i = 0;
    j = 0;
    k = 0;
    while (i < x && j < y) {
        if (X[i] <= Y[j]) {
            
            Z[k] = X[i];
            i++;
            k++;
        }
        else {
            
            Z[k] = Y[j];
            j++;
            k++;
        }
    }
    
    while (i < x) {
        Z[k] = X[i];
        i++;
        k++;
    }
    
    while (j < y) {
        Z[k] = Y[j];
        j++;
        k++;
    }
}

void mergeSort(int* p, int length)
{
    int i;
    int *p1, *p2;
    int length1, length2;

    if (length < 2)
        return; 

    
    length1 = length / 2; 
    length2 = length - length1; 
    p1 = (int*)malloc(sizeof(int) * length1);
    p2 = (int*)malloc(sizeof(int) * length2);

    
    for (i = 0; i < length1; i++) {
        p1[i] = p[i];
    }
    
    for (i = 0; i < length2; i++) {
        p2[i] = p[i + length1];
    }
    
    mergeSort(p1, length1);
    mergeSort(p2, length2);

    
    merge(p1, length1, p2, length2, p);
}

int main()
{
	
    int* A;
    int i;
    int length;
    int* A2;
    int j;
    int length2;



    length = 10;
    A = (int*)malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	
    clock_t t;

    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );

    printf ("\nlength %d.\n", length );


    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  *1000 );

    

    length2 = 10;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	
    clock_t t2;

    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",((float)t2)/CLOCKS_PER_SEC  *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );

    length = 20;

    A = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	


    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );
    printf ("\nlength %d.\n", length );
    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  *1000 );

   

    length2 = 20;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	
    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",((float)t2)/CLOCKS_PER_SEC  *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );



    length = 40;
    A = (int*)malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	

    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );

    printf ("\nlength %d.\n", length );


    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  *1000 );

    

    length2 = 40;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	

    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",((float)t2)/CLOCKS_PER_SEC  *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );

    length = 80;

    A = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	


    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );
    printf ("\nlength %d.\n", length );
    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  *1000 );

   

    length2 = 80;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	
    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",((float)t2)/CLOCKS_PER_SEC  *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );




    length = 160;
    A = (int*)malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	

    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );

    printf ("\nlength %d.\n", length );


    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  *1000 );

    

    length2 = 160;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	

    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",((float)t2)/CLOCKS_PER_SEC  *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );

    length = 320;

    A = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	


    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );
    printf ("\nlength %d.\n", length );
    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  *1000 );

   

    length2 = 320;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	
    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",((float)t2)/CLOCKS_PER_SEC  *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );





    length = 640;
    A = (int*)malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	

    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );

    printf ("\nlength %d.\n", length );


    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  *1000 );

    

    length2 = 640;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	

    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",((float)t2)/CLOCKS_PER_SEC  *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );

    length = 1280;

    A = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	


    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );
    printf ("\nlength %d.\n", length );
    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  * 1000 );

   

    length2 = 1280;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	
    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",(((float)t2)/CLOCKS_PER_SEC ) *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );

   length = 2560;

    A = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	


    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );
    printf ("\nlength %d.\n", length );
    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  * 1000 );

   

    length2 = 2560;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	
    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",(((float)t2)/CLOCKS_PER_SEC ) *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );


   length = 5120;

    A = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	


    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );
    printf ("\nlength %d.\n", length );
    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  * 1000 );

   

    length2 = 5120;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	
    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",(((float)t2)/CLOCKS_PER_SEC ) *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );



   length = 10240;

    A = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	


    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );
    printf ("\nlength %d.\n", length );
    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  * 1000 );

   

    length2 = 10240;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	
    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",(((float)t2)/CLOCKS_PER_SEC ) *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );



   length = 20480;

    A = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	


    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );
    printf ("\nlength %d.\n", length );
    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  * 1000 );

   

    length2 = 20480;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	
    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",(((float)t2)/CLOCKS_PER_SEC ) *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );



   length = 50960;

    A = (int*)malloc(sizeof(int) * length);

    for (int i = 0; i < length; ++i) {
  		A[i] = rand() % 100 + 1;
  	}	


    t = clock();

    bubbleSort(A, length);

    t = clock() -t;

    printf ("---------------------------------------------------------------------------------------------" );
    printf ("\nlength %d.\n", length );
    printf ("bubbleSort took (%f milliseconds).\n",((float)t)/CLOCKS_PER_SEC  * 1000 );

   

    length2 = 50960;
    A2 = (int*)malloc(sizeof(int) * length2);



    for (int i = 0; i < length2; ++i) {
  		A2[i] = rand() % 100 + 1;
  	}	
    t2 = clock();

    mergeSort(A2, length2);

    t2 = clock() -t2;

    printf ("mergeSort took (%f milliseconds).\n",(((float)t2)/CLOCKS_PER_SEC ) *1000 );

    printf("\n");

    printf ("---------------------------------------------------------------------------------------------" );






}
