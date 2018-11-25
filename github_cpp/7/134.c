#include <iostream>
using namespace std;


void merge(int *data, int p, int q, int r)
{
	int n1, n2, i, j, k;
    int *left=NULL, *right=NULL;
 
    n1 = q-p+1; 
	n2 = r-q;
 
    left = (int *)malloc(sizeof(int)*(n1)); 
    right = (int *)malloc(sizeof(int)*(n2));
    for(i=0; i<n1; i++)  
		left[i] = data[p+i];
    for(j=0; j<n2; j++)  
		right[j] = data[q+1+j];
 
    i = j = 0; 
	k = p;
    while(i<n1 && j<n2) 
    {
		if(left[i] <= right[j])
			data[k++] = left[i++];
		else
			data[k++] = right[j++];
    }
 
    for(; i<n1; i++) 
		data[k++] = left[i];
    for(; j<n2; j++) 
		data[k++] = right[j];
}
 
void mergeSort(int *data, int p, int r)
{
    int q;
    if(p < r) 
    {
		q = (int)((p+r)/2);      
		mergeSort(data, p, q);   
		mergeSort(data, q+1, r); 
		merge(data, p, q, r);    
    }
}
int main()    
{    
    int n;    
    int* input = NULL;    
    
    cout<<"请输入数组的长度: ";    
    cin>>n;
	input = (int *)malloc(sizeof(int)*(n));
    cout<<"请对数组赋值: ";    
    for(int i=0; i<n; ++i)    
    {    
        cin>>input[i];      
    }    
    
    mergeSort(input,0,n-1);    
    
    for(int i=0; i<n; ++i)    
        cout<<input[i]<<" ";    
    cout<<endl;    
    system("pause");    
    return 0;    
}    