//
//  MergeSort.cc
//  
//
//  Created by Benjamin Johnson on 4/17/12.
//  Copyright 2012 University of Georgia. All rights reserved.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

unsigned long long totalCount = 0;

//used for testing prints out the list
void display(int list[], int size){
	cout<<"The elements of the array are:\n";
	for(int i=0; i<size ; i++){
		cout<<list[i]<<" ";
    }
    cout<<endl;
    
}

//Fills the array entered as a parameter with the file entered
//as a parameter. Reads off each number from the list and puts
//it in the right spot in the array.
void fillArray(int list[], std::ifstream &file){
    
    if(!file) {
        cout <<"Failed to open file ";
        return;
    }
    
    int n, i=0;
    while (!file.eof()) {
        file >> n;
        list[i] = n;
        i++;
    }

}

unsigned long long merge(int a[], const int low, const int mid, const int high)
{
    int * b = new int[high+1-low];
    int h,i,j,k;
    
    h=low;
    i=0;
    j=mid+1;
    while((h<=mid)&&(j<=high))
    {
        if(a[h]<=a[j])
        {
            b[i]=a[h];
            h++;
        }
        else
        {
            b[i]=a[j];
            j++;
        }
        i++;
        totalCount++;
    }
    if(h>mid)
    {
        for(k=j;k<=high;k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    else
    {
        for(k=h;k<=mid;k++)
        {
            b[i]=a[k];
            i++;
        }
    }
    for(k=0;k<=high-low;k++) 
    {
        a[k+low]=b[k];
    }
    delete[] b;
}

//recursive call of merge sort. Splits the list into smaller list 
//until they are seperated by element then calls merge to combine and sort.
void mergeSort(int a[], const int low, const int high)   
{
    int mid;
    if(low<high)
    {
        mid=(low+high)/2;
        mergeSort(a, low,mid);
        mergeSort(a, mid+1,high);
        merge(a, low,mid,high);
    }
}

int main (int argc, char *argv[]){
    if (argc != 2){
        printf("Please enter number of elements to be sorted\n");
        return -1;
    }

    int amount;
    amount = atoi(argv[1]);
    
    int list1[amount], list2[amount], list3[amount], list4[amount], list5[amount], list6[amount], list7[amount], list8[amount], list9[amount], list10[amount], list11[amount], list12[amount], list13[amount], list14[amount], list15[amount], list16[amount], list17[amount], list18[amount], list19[amount], list20[amount];
    
    std::ifstream file1("num1.txt");
    std::ifstream file2("num2.txt");
    std::ifstream file3("num3.txt");
    std::ifstream file4("num4.txt");
    std::ifstream file5("num5.txt");
    std::ifstream file6("num6.txt");
    std::ifstream file7("num7.txt");
    std::ifstream file8("num8.txt");
    std::ifstream file9("num9.txt");
    std::ifstream file10("num10.txt");
    std::ifstream file11("num11.txt");
    std::ifstream file12("num12.txt");
    std::ifstream file13("num13.txt");
    std::ifstream file14("num14.txt");
    std::ifstream file15("num15.txt");
    std::ifstream file16("num16.txt");
    std::ifstream file17("num17.txt");
    std::ifstream file18("num18.txt");
    std::ifstream file19("num19.txt");
    std::ifstream file20("num20.txt");
  
    fillArray(list1, file1);
    fillArray(list2, file2);
    fillArray(list3, file3);
    fillArray(list4, file4);
    fillArray(list5, file5);
    fillArray(list6, file6);
    fillArray(list7, file7);
    fillArray(list8, file8);
    fillArray(list9, file9);
    fillArray(list10, file10);
    fillArray(list11, file11);
    fillArray(list12, file12);
    fillArray(list13, file13);
    fillArray(list14, file14);
    fillArray(list15, file15);
    fillArray(list16, file16);
    fillArray(list17, file17);
    fillArray(list18, file18);
    fillArray(list19, file19);
    fillArray(list20, file20);
    
    mergeSort(list1 , 0 , (amount-1));
    mergeSort(list2 , 0 , (amount-1));
    mergeSort(list3 , 0 , (amount-1));
    mergeSort(list4 , 0 , (amount-1));
    mergeSort(list5 , 0 , (amount-1));
    mergeSort(list6 , 0 , (amount-1));
    mergeSort(list7 , 0 , (amount-1));
    mergeSort(list8 , 0 , (amount-1));
    mergeSort(list9 , 0 , (amount-1));
    mergeSort(list10 , 0 , (amount-1));
    mergeSort(list11 , 0 , (amount-1));
    mergeSort(list12 , 0 , (amount-1));
    mergeSort(list13 , 0 , (amount-1));
    mergeSort(list14 , 0 , (amount-1));
    mergeSort(list15 , 0 , (amount-1));
    mergeSort(list16 , 0 , (amount-1));
    mergeSort(list17 , 0 , (amount-1));
    mergeSort(list18 , 0 , (amount-1));
    mergeSort(list19 , 0 , (amount-1));
    mergeSort(list20 , 0 , (amount-1));
    
    unsigned long long average = totalCount/20;
    
    ofstream output("outputMerge.txt", ios::app);
    if (output.is_open())
    {
        output <<"average comparisons for "<<amount<<" elements "<<average<<endl;
        output.close();
    }

}
