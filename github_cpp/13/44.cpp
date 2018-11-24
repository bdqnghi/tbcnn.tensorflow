#include <iostream>
using namespace std;

/*合并数组data[p~q]和data[q+1~r]*/
void merge(int *data, int p, int q, int r)
{
	int n1, n2, i, j, k;
    int *left=NULL, *right=NULL;
 
    n1 = q-p+1; 
	n2 = r-q;
 
    left = (int *)malloc(sizeof(int)*(n1)); 
    right = (int *)malloc(sizeof(int)*(n2));
    for(i=0; i<n1; i++)  //对左数组赋值
		left[i] = data[p+i];
    for(j=0; j<n2; j++)  //对右数组赋值
		right[j] = data[q+1+j];
 
    i = j = 0; 
	k = p;
    while(i<n1 && j<n2) //将数组元素值两两比较，并合并到data数组
    {
		if(left[i] <= right[j])
			data[k++] = left[i++];
		else
			data[k++] = right[j++];
    }
 
    for(; i<n1; i++) //如果左数组有元素剩余，则将剩余元素合并到data数组
		data[k++] = left[i];
    for(; j<n2; j++) //如果右数组有元素剩余，则将剩余元素合并到data数组
		data[k++] = right[j];
}
 
void mergeSort(int *data, int p, int r)
{
    int q;
    if(p < r) //只有一个或无记录时不须排序 
    {
		q = (int)((p+r)/2);      //将data数组分成两半   
		mergeSort(data, p, q);   //递归拆分左数组
		mergeSort(data, q+1, r); //递归拆分右数组
		merge(data, p, q, r);    //合并数组
    }
}
int main()    
{    
    int n;    
    int* input = NULL;    
    //输入数据    
    cout<<"请输入数组的长度: ";    
    cin>>n;
	input = (int *)malloc(sizeof(int)*(n));
    cout<<"请对数组赋值: ";    
    for(int i=0; i<n; ++i)    
    {    
        cin>>input[i];      
    }    
    //处理数据    
    mergeSort(input,0,n-1);    
    //输出结果    
    for(int i=0; i<n; ++i)    
        cout<<input[i]<<" ";    
    cout<<endl;    
    system("pause");    
    return 0;    
}    